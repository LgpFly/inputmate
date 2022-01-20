#ifndef _CONFIGURATION_H__
#define _CONFIGURATION_H__

#include "nocopyable.h"

#include <string>
#include <map>

using namespace std;

class Configuration
: public Nocopyable
{

public:
    Configuration(const string &file_path);
    
    string getEnglishDir() const{
        return _english_dir;
    }

    string getChineseDir() const{
        return _chinese_dir;
    }

private:
    string _file_path;
    string _english_dir;
    string _chinese_dir;

};

template<typename T>
class Singleton{
    
public:
    template<typename ...Args>
        static T* getInstance(Args ...args){
            if(!_pInstance)
                _pInstance = new T(args...);
            return _pInstance;
        }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
    }

private:
    Singleton();
    ~Singleton();
    static T *_pInstance;
};

template<typename T>
T* Singleton<T>::_pInstance = NULL;


#endif
