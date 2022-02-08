#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <netinet/in.h>
#include <string>

class InetAddress{
public:
    // 构造函数
    InetAddress(short port);
    InetAddress(const char* p_ip, short port);
    InetAddress(const struct sockaddr_in& addr);
    
    // 获取信息的函数
    struct sockaddr_in* getSockAddrPtr();
    std::string ip() const;
    unsigned short port() const;



private:
    struct sockaddr_in _addr;
};



#endif

