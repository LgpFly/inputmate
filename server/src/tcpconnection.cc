#include <string.h>
#include <stdio.h>
#include <iostream>

#include "../include/tcpconnection.h"
#include "../include/epollpoller.h"



TcpConnection::TcpConnection(int sockfd, EpollPoller* loop)
    :_sockfd(sockfd), _sockio(sockfd), _local_addr(Socket::getLocalAddr(sockfd)), 
    _peer_addr(Socket::getPeerAddr(sockfd)), _shutdown_write(false), 
    _loop(loop)
{
    _sockfd.nonblock();
}

TcpConnection::~TcpConnection(){
    if(!_shutdown_write){
        _shutdown_write = true;
        shutdown();
    }
    printf("~TcpConnection()\n");
}

std::string TcpConnection::receive(){
    char buf[1024];
    // memset(buf, 0, sizeof(buf));

    // size_t ret = _sockio.readLine(buf, sizeof(buf));
    int len;
    recv(_sockfd.fd(), &len, 4, 0);
    memset(buf, 0, sizeof(buf));
    int ret = recv(_sockfd.fd(), buf, len, 0);
    if(0 == ret){
        return std::string();
    }else{
        return std::string(buf);
    }
}

void TcpConnection::sendX(const std::string msg){

    int len = msg.size();
    std::cout << "msg:" << msg << "(" << len << ")" << std::endl;
    // _sockio.writen((const char*)&len, sizeof(int));
    // _sockio.writen(msg.c_str(), len);
    send(_sockfd.fd(), &len, 4, 0);
    send(_sockfd.fd(), msg.c_str(), len, 0);
}

void TcpConnection::shutdown(){
    
    if(!_shutdown_write){
        _sockfd.shutdownWrite();
    }

    _shutdown_write = true;
}

std::string TcpConnection::toString(){

    char buf[300];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%s:%d -> %s:%d", 
             _local_addr.ip().c_str(), _local_addr.port(),
             _peer_addr.ip().c_str(), _peer_addr.port());

    return std::string(buf);
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	_on_connection_cb = cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	_on_message_cb = cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	_on_close_cb = cb;
}

void TcpConnection::handleConnectionCallback()
{
	if(_on_connection_cb)
		_on_connection_cb(shared_from_this());
}

void TcpConnection::handleMessageCallback()
{
	if(_on_message_cb)
		_on_message_cb(shared_from_this());
}

void TcpConnection::handleCloseCallback()
{
	if(_on_close_cb)
		_on_close_cb(shared_from_this());
}
	
void TcpConnection::sendInLoop(const std::string & msg)
{
	_loop->runInLoop(std::bind(&TcpConnection::sendX, this, msg));
}


