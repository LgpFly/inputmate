#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <map>
#include <string>

#include "../include/nocopyable.h"

#define CONFPATH "/home/l/secondproject/inputmate/server/config/config.txt"

using std::map;
using std::string;

class Configuration
: public Nocopyable
{
public:
    Configuration(string);
    ~Configuration() = default;
    string getDictDir() const;
    string getIndexDir() const;
    string getIp() const;
    unsigned short getPort() const;
    string getCache() const;


private:
    string _file_path;
    map<string, string> _conf;
};

template<typename T>
class Singleton{
public:
    template<typename ...Args>
    static T* getInstance(Args ...args){
        if(!_p_instance){
            _p_instance = new T(args...);
        }
        return _p_instance;
    }

    static void destroy(){
        if(_p_instance){
            delete _p_instance;
        }
    }

private:
    static T* _p_instance;
    Singleton();
    ~Singleton();
};

template<typename T>
T* Singleton<T>::_p_instance = NULL;



#endif
