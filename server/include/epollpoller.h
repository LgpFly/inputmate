#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>
#include <string>

#include "./nocopyable.h"
#include "./tcpconnection.h"
#include "./mutexlock.h"

class Acceptor;

class EpollPoller
:Nocopyable{

public:
    typedef TcpConnection::TcpConnectionCallback EpollCallback;
    typedef std::function<void()> Functor;

    EpollPoller(Acceptor& acceptor);
    ~EpollPoller();

    void loop();
    void unloop();
    void runInLoop(const Functor && cb);
    void doPendingFunctors();
    void wakeup();

    void setConnectionCallback(EpollCallback cb);
	void setMessageCallback(EpollCallback cb);
	void setCloseCallback(EpollCallback cb);

private:
	void waitEpollfd();
	void handleConnection();
	void handleMessage(int peerfd);
	void handleRead();

private:
    Acceptor& _acceptor;
    int _epfd;
    int _evfd;
    int _listenfd;
    bool _is_looping;

    MutexLock _mutex;
    std::vector<Functor> _pending_functors;

    typedef std::vector<struct epoll_event> EventList;
    EventList _event_list;
    typedef std::map<int, TcpConnectionPtr> ConnectionMap;
    ConnectionMap _conn_map;

    EpollCallback _on_connection_cb;
    EpollCallback _on_message_cb;
    EpollCallback _on_close_cb;
};


#endif
