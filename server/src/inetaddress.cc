#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


#include "../include/inetaddress.h"

InetAddress::InetAddress(short port){
    ::memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const char* p_ip, short port){
    ::memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(p_ip);
}

InetAddress::InetAddress(const struct sockaddr_in& addr)
    :_addr(addr)
{}

struct sockaddr_in* InetAddress::getSockAddrPtr(){
    return &_addr;
}

std::string InetAddress::ip() const{
    return std::string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const{
    return ntohs(_addr.sin_port);
}
