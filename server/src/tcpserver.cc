#include <iostream>

#include "../include/tcpserver.h"
#include "../include/inetaddress.h"
#include "../include/socketutil.h"
#include "../include/epollpoller.h"

using std::cout;
using std::endl;

TcpServer::TcpServer(const string & ip, unsigned short port)
: _acceptor(creatSockFd(), InetAddress(ip.c_str(), port))
, _poller(_acceptor)
{}

void TcpServer::start()
{
	_acceptor.ready();
	_poller.setConnectionCallback(_connection_callback);
	_poller.setMessageCallback(_message_callback);
	_poller.setCloseCallback(_close_callback);
	_poller.loop();
}

void TcpServer::stop()
{
	_poller.unloop();
}


void TcpServer::setConnectionCallback(TcpServerCallback cb)
{	_connection_callback = cb;	}
void TcpServer::setMessageCallback(TcpServerCallback cb)
{	_message_callback = cb;	}
void TcpServer::setCloseCallback(TcpServerCallback cb)
{	_close_callback = cb;	}
