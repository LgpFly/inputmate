#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "socket.h"
#include "inetaddress.h"

class Acceptor{

public:
    Acceptor(int listen_sockfd, const InetAddress& addr);

    void ready();
    int acceptor();
    
    int fd() const {return _listen_sockfd.fd();}
    
private:

    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();


private:
    Socket _listen_sockfd;
    InetAddress _addr;
};


#endif
