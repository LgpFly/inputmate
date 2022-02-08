#include <stdlib.h>
#include <utility>
#include <fstream>
#include <iostream>

#include "../include/configuration.h"

using namespace std;

Configuration::Configuration(string file_path)
    :_file_path(file_path)
{
    ifstream ifs(_file_path);
    if(!ifs){
        cout << "config read error" << endl;
    }
    string key, value;
    while(ifs >> key){
        ifs >> value;
        _conf.insert(make_pair(key, value));
    }
    ifs.close();
}

string Configuration::getDictDir() const{
    auto cit = _conf.find("mydict");
    if(cit == _conf.end()){
        return "";
    }
    return cit->second;
}

string Configuration::getIndexDir() const{
    auto cit = _conf.find("myindex");
    if(cit == _conf.end()){
        return "";
    }
    return cit->second;
}

string Configuration::getIp() const{
    auto cit = _conf.find("myip");
    if(cit == _conf.end()){
        return "";
    }
    return cit->second;
}

unsigned short Configuration::getPort() const{
    auto cit = _conf.find("myport");
    if(cit == _conf.end()){
        return 0;
    }
    return atoi(cit->second.c_str());
}

string Configuration::getCache() const{
    auto cit = _conf.find("mycache");
    if(cit == _conf.end()){
        return "";
    }
    return cit->second;
}


