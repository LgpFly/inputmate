#include <iostream>


#include "../include/acceptor.h"
#include "../include/socketutil.h"

using std::cout;
using std::endl;

Acceptor::Acceptor(int listen_sockfd, const InetAddress& addr)
    :_listen_sockfd(listen_sockfd), _addr(addr)
{}

void Acceptor::ready(){
    setReuseAddr(true);
    setReusePort(true);
    bind();
    listen();
}

int Acceptor::acceptor(){
    int peer_fd = ::accept(_listen_sockfd.fd(), NULL, NULL);
    if(-1 == peer_fd){
        perror("accept");
    }
    return peer_fd;
}

void Acceptor::setReuseAddr(bool flag){
    int on = (flag ? 1 : 0);
    if(-1 == ::setsockopt(_listen_sockfd.fd(), SOL_SOCKET, SO_REUSEADDR, &on, 
                    static_cast<socklen_t>(sizeof(on))))
    {
        perror("setReuseAddr error");
        ::close(_listen_sockfd.fd());
        exit(EXIT_FAILURE);
    }
}


void Acceptor::setReusePort(bool flag){
    
#ifdef SO_REUSEPORT
	int on = (flag ? 1 : 0);
	if(::setsockopt(_listen_sockfd.fd(), 
				    SOL_SOCKET,
					SO_REUSEPORT,
					&on,
					static_cast<socklen_t>(sizeof(on))) == -1)
	{
		perror("setsockopt reuseport error");
		::close(_listen_sockfd.fd());
		exit(EXIT_FAILURE);
	}
#else
	if(flag)
	{
		fprintf(stderr, "SO_REUSEPORT is not supported!\n");
	}
#endif
}

void Acceptor::bind(){
    if(-1 == ::bind(_listen_sockfd.fd(), (struct sockaddr*)_addr.getSockAddrPtr(), sizeof(InetAddress)))
    {
        perror("bind error");
		::close(_listen_sockfd.fd());
		exit(EXIT_FAILURE);
    }


}

void Acceptor::listen(){
    if(-1 == ::listen(_listen_sockfd.fd(), 10))
    {
        perror("listen error");
		::close(_listen_sockfd.fd());
		exit(EXIT_FAILURE);
    }
}

