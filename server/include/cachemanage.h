#ifndef __CACHEMANAGE_H__
#define __CACHEMANAGE_H__

#include <vector>

#include "../include/cache.h"

#define THREADNUM 4

class CacheManage{

public:

    CacheManage(string);
    void init(string);
    Cache& getCache(int);
    void periodUpdate();

private:
    string _cache_filepath;
    std::vector<Cache> _cache_list;
};



#endif
