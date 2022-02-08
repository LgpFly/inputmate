#ifndef __MYDICT_H__
#define __MYDICT_H__

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

struct MyResult{
    string word;
    int freq;
    int dist;
};

class Mydict{
public:
    Mydict(const string dict_dir, const string index_dir){
        ifstream ifs1(dict_dir);
        ifstream ifs2(index_dir);

        if(!ifs1 || !ifs2){
            cout << "dict or index file open error" << endl;
        }
        string key;
        int value;
        ifs1 >> value;
        _dict.push_back(std::make_pair(string(""), value));
        while(ifs1 >> key){
            ifs1 >> value;
            _dict.push_back(std::make_pair(key, value));
        }

        string line;
        while(getline(ifs2, line)){
            istringstream iss(line);
            string idx_key;
            int idx_value;
            set<int> tmp;
            iss >> idx_key;
            while(iss >> idx_value){
                tmp.insert(idx_value);
            }
            _index.insert(make_pair(idx_key, tmp));
        }
    }

    vector<pair<string, int>>& getDict(){
        return _dict;
    }

    map<string, set<int>>& getIndex(){
        return _index;
    }

private:
    vector<pair<string, int>> _dict;
    map<string, set<int>> _index;
};



#endif
