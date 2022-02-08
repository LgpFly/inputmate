#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

#include "../include/mytask.h"

extern __thread int t_num;
bool MyTask::response(Cache &cache){
    if(cache.find(_querry)){
        _p_conn->sendInLoop(cache[_querry]);
        return true;
    }
    return false;
}

vector<string> MyTask::getOne(const string &word){
    
    auto cit = word.begin();
    vector<string> ret;
    while(cit != word.end()){
        if(224 == (*cit & 224)){
            string str;
            str.append(cit, cit + 3);
            ret.push_back(str);
            cit += 3;
        }else if(240 == (*cit & 240)){
            string str;
            str.append(cit, cit + 4);
            ret.push_back(str);
            cit += 4;
        }else{
            string str(1, *cit);
            ret.push_back(str);
            cit++;
        }
    }
    return ret;
}

int MyTask::distance(const string &rhs){
    cout << "distance start" << endl;
    vector<string> split_querry = getOne(_querry);
    vector<string> split_cancida = getOne(rhs);
    
    int len1, len2;
    len1 = split_querry.size();
    len2 = split_cancida.size();
    int edit[len1][len2];
    int i, j;
    for(i = 0; i < len1; ++i){
        for(j = 0; j < len2; ++j){
            edit[i][j] = 0;
        }
    }

    for(i = 0; i <= len1; ++i){
        edit[i][0] = i;
    }
    for(j = 0; j <= len2; ++j){
        edit[0][j] = j;
    }
    for(i = 1; i <= len1; ++i){
        for(j = 1; j <= len2; ++j){
            int cost;
            if(split_querry[i - 1] == split_cancida[j - 1]){   
                cost = 0;   
            }else{
                cost = 1;
            }
            int deletion = edit[i - 1][j] + 1;
            int insertion = edit[i][j - 1] + 1;
            int substitution = edit[i - 1][j - 1] + cost;
            edit[i][j] = min(deletion, min(insertion, substitution));
        }
    }
    return edit[len1][len2];
}

void MyTask::statistic(set<int> &iset){
    
    vector<pair<string, int>> dict = Singleton<Mydict>::getInstance(Singleton<Configuration>::getInstance(CONFPATH)->getDictDir(),  
                                                                     Singleton<Configuration>::getInstance(CONFPATH)->getIndexDir()) 
                                      -> getDict();

    for(auto &idx : iset){
        string key = dict[idx].first;
        // cout << "will compare is" << key << endl;
        int dist = distance(key);
        if(dist < 3){
            MyResult res;
            res.word = key;
            res.dist = dist;
            res.freq = dict[idx].second;
            _result.push(res);
        }
    }
}

void MyTask::querryIndex(){
    map<string, set<int>> index = (Singleton<Mydict>::getInstance(Singleton<Configuration>::getInstance(CONFPATH)->getDictDir(), 
                                                                    Singleton<Configuration>::getInstance(CONFPATH)->getIndexDir() 
                                                                    ))->getIndex();
    vector<string> split_word = getOne(_querry);
    // for(auto &one : split_word){
    //     cout << one << " ";
    // }
    // cout << endl;
    
    set<int> all;
    for(auto one : split_word){
        auto cit = index.find(one);
        if(cit != index.end()){
            for(auto &idx : cit->second){
                all.insert(idx);
            }
        }
    }


    statistic(all);

}



void MyTask::execute(){

    cout << "this is execute()" << endl;
    cout << "this is in execute" << this->_querry <<endl;
    printf("_querry:%s\n", _querry.c_str());
    // 这里可能有问题
    Cache &mycache = Singleton<CacheManage>::getInstance(Singleton<Configuration>::getInstance(CONFPATH)->getCache())->getCache(t_num);
    
    if(response(mycache)){
        return;
    }else{
        querryIndex();


        // 打印测试
        // int size  = _result.size();
        // for(int i = 0; i < size; ++i){
        //     MyResult res = _result.top();
        //     cout << res.word << "," << res.dist << "," << res.freq << endl;
        //     _result.pop();
        //     
        // }
        
        Json::FastWriter writeinfo;
        Json::Value array_obj;
        while(!_result.empty()){
            Json::Value new_item;
            new_item[""] = _result.top().word;
            _result.pop();
            array_obj.append(new_item);
        }
        string res = writeinfo.write(array_obj);
        mycache.addElement(_querry, res);
        _p_conn->sendInLoop(res);
        
    }
}


