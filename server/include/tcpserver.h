#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <string>

#include "./acceptor.h"
#include "./epollpoller.h"

using std::string;

class TcpServer{
public:

    typedef EpollPoller::EpollCallback TcpServerCallback;
    TcpServer(const string & ip, unsigned short port);
	TcpServer(unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);

private:
    Acceptor _acceptor;
    EpollPoller _poller;

    TcpServerCallback _connection_callback;
	TcpServerCallback _message_callback;
	TcpServerCallback _close_callback;
};



#endif
