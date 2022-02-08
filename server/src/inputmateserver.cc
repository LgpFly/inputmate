#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <functional>

#include "../include/inputmateserver.h"
#include "../include/mytask.h"

void InputMateServer::onConnection(const TcpConnectionPtr& conn)
{
	cout << conn->toString() << endl;
	conn -> sendX("hello,welcome to Chat Server.");
}
void InputMateServer::onMessage(const TcpConnectionPtr& conn)
{
	string s(conn -> receive());
	cout << "receive:" << s << endl;
	MyTask task(s, conn);
	_threadpoll.addTask(std::bind(&MyTask::execute, &task));
	cout << "> add task to threadpool" << endl;
}
void InputMateServer::onClose(const TcpConnectionPtr& conn)
{
	::printf("%s close\n",conn -> toString().c_str());
}
InputMateServer::InputMateServer(const string& ip,
							unsigned short port,
							size_t thread_num,
							size_t que_size)
	:_tcpserver(ip, port)
	,_threadpoll(thread_num, que_size)
{}
void InputMateServer::start()
{
	_threadpoll.start();
	_tcpserver.setConnectionCallback(std::bind(&InputMateServer::onConnection,this,std::placeholders::_1));
	_tcpserver.setMessageCallback(std::bind(&InputMateServer::onMessage,this,std::placeholders::_1));
	_tcpserver.setCloseCallback(std::bind(&InputMateServer::onClose,this,std::placeholders::_1));
	_tcpserver.start();
}
