#include <iostream>
#include <functional>

#include "../include/inputmateserver.h"
#include "../include/cachemanage.h"
#include "../include/configuration.h"
#include "../include/timerthread.h"
using std::cout;
using std::endl;

int main(){
        
    // short port = 8888; 
    // InputMateServer input_mate_server("192.168.117.130", port, 4, 10);
    
    CacheManage *my_cache_manage = Singleton<CacheManage>::getInstance(Singleton<Configuration>::getInstance(CONFPATH)->getCache());
    TimerThread timer(5, 6, std::bind(&CacheManage::periodUpdate, my_cache_manage));
    cout << Singleton<Configuration>::getInstance(CONFPATH)->getIp() << endl;
    cout << Singleton<Configuration>::getInstance(CONFPATH)->getPort() << endl;
    InputMateServer input_mate_server(Singleton<Configuration>::getInstance(CONFPATH)->getIp(),
                                      Singleton<Configuration>::getInstance(CONFPATH)->getPort(),
                                      4, 10);
    input_mate_server.start();
    return 0;
}
