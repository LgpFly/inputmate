#ifndef __INPUTMATESERVER_H__
#define __INPUTMATESERVER_H__

#include "./tcpserver.h"
#include "./threadpool.h"

class InputMateServer{
public:
    
    InputMateServer(const string& ip,
							   unsigned short port,
							   size_t threadNUM,
							   size_t queSize);
	void start();

private:
    void onConnection(const TcpConnectionPtr &);
	void onMessage(const TcpConnectionPtr&);
	void onClose(const TcpConnectionPtr&);
private:
	TcpServer _tcpserver;
	ThreadPool _threadpoll;
};



#endif
