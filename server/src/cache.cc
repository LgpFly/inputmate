#include "../include/cache.h"

#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

void Cache::readFromFile(string file_path){

    ifstream ifs(file_path);
    if(!ifs){
        cout << "cache open fil_path errore" << endl;
    }
    string querry, result;
    while(ifs >> querry && !ifs.eof()){
        ifs >> result;
        _hash_table[querry] = result;
    }
}

void Cache::writeToFile(string file_path){
    ofstream ofs(file_path);
    if(!ofs){
        cout << "cache write file error" << endl;
    }
    for(auto &mypair : _hash_table){
        ofs << mypair.first << " ";
        ofs << mypair.second << endl;
    }
}

void Cache::addElement(string querry, string result){

    _hash_table[querry] = result;

}


void Cache::update(const Cache &cache){

    for(auto &mypair : cache._hash_table){
        auto cit = _hash_table.find(mypair.first);
        if(cit == _hash_table.end()){
            _hash_table.insert(move(mypair));
        }
    }
}

bool Cache::find(string querry){
    auto cit = _hash_table.find(querry);
    if(cit == _hash_table.end()){
        return false;
    }
    return true;

}
string& Cache::operator[](string key){
    return _hash_table[key];
}
