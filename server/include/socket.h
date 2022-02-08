#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "nocopyable.h"

class InetAddress;
class Socket
:Nocopyable{
public:
    Socket(int sockfd);
    Socket();
    ~Socket();

    void shutdownWrite();
    int fd() const;
    void nonblock();

    static InetAddress getLocalAddr(int sockfd);
    static InetAddress getPeerAddr(int sockfd);

private:
    int _sockfd;
};


#endif
