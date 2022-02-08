#include "../include/socket.h"
#include "../include/socketutil.h"
#include "../include/inetaddress.h"

Socket::Socket(int sockfd)
    :_sockfd(sockfd)
{}

Socket::Socket()
    :_sockfd(creatSockFd())
{}

Socket::~Socket(){
    close(_sockfd);
}

void Socket::nonblock(){
    setNonblock(_sockfd);
}

void Socket::shutdownWrite(){
    if(-1 == ::shutdown(_sockfd, SHUT_WR))
        perror("shutdown_wr");
}

int Socket::fd() const{
    return _sockfd;
}


InetAddress Socket::getLocalAddr(int sockfd){
    struct sockaddr_in addr;
    socklen_t len = sizeof(sockaddr_in);
    if(-1 == ::getsockname(sockfd, (struct sockaddr*)&addr, &len)){
        perror("getsockname");
    }
    return InetAddress(addr);
}

InetAddress Socket::getPeerAddr(int sockfd){
    struct sockaddr_in addr;
    socklen_t len = sizeof(sockaddr_in);
    if(-1 == getpeername(sockfd, (struct sockaddr*)&addr, &len)){
        perror("getpeername");
    }
    return InetAddress(addr);
}
