#include <fstream>
#include <sstream>
#include <iostream>

#include "getindex.h"

using namespace std;

GetIndex::GetIndex(const string& source_file_path, const string& aid_file_path, 
                   const string& stop_word_file_path)
    :_source_file_path(source_file_path), _aid_file_path(aid_file_path), _stop_word_file_path(stop_word_file_path)
{
    ifstream ifs(_source_file_path);
    if(!ifs){
        cout << "source_file_path open error" <<endl;
    }
    string line;
    while(getline(ifs, line)){
        istringstream iss(line);
        string key;
        int value;
        iss >> key >> value;
        _dict.push_back(make_pair(key, value));
    }

    ifstream ifs_stop(_stop_word_file_path);
    if(!ifs_stop){
        cout << "stop file open error" << endl;
    }

    string stop_word;
    while(ifs_stop >> stop_word, !ifs_stop.eof()){
        _stop_words.insert(stop_word);
    }
}


GetIndex::~GetIndex(){

}

bool GetIndex::isEnglish(const string &rhs) const{
    char ch = *(rhs.begin());
    if(ch < 0)
        return false;
    return true;
}

vector<string> GetIndex::getOneCharacter(const string& word){
    vector<string> tmp;
    auto cit = word.begin();
    while(cit != word.end()){

        if((*cit & 224) == 224){
            string one;
            one.append(cit, cit + 3);
            tmp.push_back(one);
            cit += 3;
        }else if((*cit & 240) == 240){
            string one;
            one.append(cit, cit + 4);
            tmp.push_back(one);
            cit += 4;
        }else
            break;
    }
    return tmp;
}

void GetIndex::constructIndex(){
    for(size_t i =0; i < _dict.size(); ++i){
        
        string tmp = _dict[i].first;
        if(isEnglish(tmp)){
            for(auto ch : tmp){
                string ss(1, ch);
                if(isalpha(ch)){
                    auto cit = _index.find(ss);
                    if(cit == _index.end()){
                        set<int> smp;
                        smp.insert(i);
                        _index.insert(make_pair(ss, smp));
                    }else{
                        cit->second.insert(i);
                    }
                }
            }
        }else{
            vector<string> one_word = getOneCharacter(tmp);
            for(auto one : one_word){
                if(_stop_words.find(one) == _stop_words.end()){
                    auto it = _index.find(one);
                    if(it == _index.end()){
                        set<int> smp;
                        smp.insert(i);
                        _index.insert(make_pair(one, smp));
                    }else{
                        it->second.insert(i);
                    }
                }
            }
        }


    }
}


void GetIndex::storeIndex(){
    ofstream ofs(_aid_file_path);
    if(!ofs){
        cout << "aid_index open error" << endl; 
    }
    for(auto data : _index){
        ofs << data.first << " ";
        for(auto line_num : data.second){
            ofs << line_num << " ";
        }
        ofs << endl;
    }

    ofs.close();
}
