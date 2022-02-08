#include <iostream>
#include <fstream>
#include <utility>

#include "../include/cachemanage.h"

using namespace std;

CacheManage::CacheManage(string cache_filepath){
    init(cache_filepath);
}

void CacheManage::init(string cache_filepath){
    _cache_filepath = cache_filepath;
    _cache_list.reserve(THREADNUM);
    Cache tmp;
    tmp.readFromFile(_cache_filepath);
    for(int i = 0; i < THREADNUM; ++i){
        _cache_list.push_back(std::move(tmp));
    }
}

Cache& CacheManage::getCache(int index){
    return _cache_list[index];
}

void CacheManage::periodUpdate(){
    auto cit = _cache_list.begin();
    Cache last_write = *(cit++);
    for(; cit < _cache_list.end(); ++cit){
        last_write.update(*cit);
    }

    for(cit = _cache_list.begin() + 1; cit != _cache_list.end(); ++cit){
        (*cit).update(last_write);
    }
    
    std::cout << "要写入到文件中去了" << std::endl;
    last_write.writeToFile(_cache_filepath);
}
