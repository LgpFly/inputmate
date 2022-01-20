#include <cctype>
#include <utility>
#include <fstream>
#include <iostream>

#include "dictproducer.h"
#define FIRSTSIZE 10000

using namespace std;

DictProducer::DictProducer(const string english_dir, const string chinese_dir, 
             const string &aid_file_path, SplitToolJieba *p_split_tool)
    :_english_dir(english_dir), _chinese_dir(chinese_dir), 
    _aid_file_path(aid_file_path)
{
    _split_tool.reset(p_split_tool);
    ifstream ifs_english(_english_dir);
    ifstream ifs_chinese(_chinese_dir);
    string file_path;
    if(!ifs_english || !ifs_chinese){
        cout << "dict file open error" << endl;
    }
    while(ifs_english  >> file_path){
        _english_files.push_back(file_path);
    }
    while(ifs_chinese >> file_path){
        _chinese_files.push_back(file_path);
    }
    _indict.reserve(FIRSTSIZE);
}

void DictProducer::processEnglishWord(string & word){
    auto cit = word.begin();
    // for(; cit != word.end(); ++cit){
    //     if(!isalpha(*cit)){
    //         if(cit == word.begin())
    //             word.erase(cit);
    //         else{
    //             word.erase(cit);
    //             --cit;
    //         }
    //     }else if(isupper(*cit)){
    //         *cit = towlower(*cit);
    //     }
    // }
    while(cit != word.end()){
        if(!isalpha(*cit)){
            word.erase(cit);
        }else if(isupper(*cit)){
            *cit = tolower(*cit);
            ++cit;
        }else{
            ++cit;
        }
    }
    
}

void DictProducer::processChineseWord(string & word){

    auto cit = word.begin();
    // for(; cit != word.end(); ++cit){
    //     if(isalnum(*cit)){
    //         word.erase(*cit);
    //         cit--;
    //     }
    // }
    while(cit != word.end()){
        if(isalnum(*cit)){
            word.erase(cit);
        }else{
            ++cit;
        }
    }
}

void DictProducer::buildEnglishDict(){

    for(auto &file_path : _english_files){
        ifstream ifs(file_path);
        if(!ifs){
            cout << "english file open error" << endl;
        }

        string word;
        while(ifs >> word){
            processEnglishWord(word);
            auto cit = _dict.find(word);
            if(word.size() > 0 && cit == _dict.end()){
                _dict.insert(make_pair(word, 1));
            }else if(cit != _dict.end()){
                ++cit->second;
            }
        }
    }
}


void DictProducer::buildChineseDict(){

    for(auto &file_path : _chinese_files){
        ifstream ifs(file_path);
        if(!ifs){
            cout << "chinese file open error" << endl;
        }

        string sentence;
        while(getline(ifs, sentence)){
            _split_tool->cut(sentence);
        }

    }

    vector<string> &results = _split_tool->getResult();
    for(auto &res : results){
        processChineseWord(res);
        auto cit = _dict.find(res);
        if(res.size() != 0 && cit == _dict.end()){
            _dict.insert(make_pair(res, 1));
        }else{
            ++cit->second;
        }
    }
}

DictProducer::~DictProducer(){}

void DictProducer::storeDict(){
    construct_indict();
    ofstream ofs(_aid_file_path);
    if(!ofs){
        cout << "open aid file error" << endl; 
    }
    for(auto & mypair : _indict){
        ofs << mypair.first << " " << mypair.second << endl;
    }

    ofs.close();
}


void DictProducer::construct_indict(){
    for(auto dict_pair : _dict){
        _indict.push_back(dict_pair);
    }
}
