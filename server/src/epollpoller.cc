
#include <assert.h>
#include <iostream>

#include "../include/epollpoller.h"
#include "../include/socketutil.h"
#include "../include/acceptor.h"

using std::cout;
using std::endl;

EpollPoller::EpollPoller(Acceptor& acceptor)
    :_acceptor(acceptor), _epfd(creatEpollFd()), 
    _evfd(creatEventFd()), _listenfd(acceptor.fd()), 
    _is_looping(false), _event_list(1024)
{
    addEpollReadFd(_epfd, _listenfd);
    addEpollReadFd(_epfd, _evfd);
}

EpollPoller::~EpollPoller(){
    ::close(_epfd);
}

void EpollPoller::loop(){
    _is_looping = true;
    while(_is_looping){
        waitEpollfd();
    }
}

void EpollPoller::unloop(){
    if(_is_looping){
        _is_looping = false;
    }
}

void EpollPoller::runInLoop(const Functor && cb)
{
	{
		MutexLockGuard mlg(_mutex);
		_pending_functors.push_back(std::move(cb));
	}
	wakeup();
}



void EpollPoller::setConnectionCallback(EpollCallback cb)
{
	_on_connection_cb = cb;
}

void EpollPoller::setMessageCallback(EpollCallback cb)
{
	_on_message_cb = cb;
}

void EpollPoller::setCloseCallback(EpollCallback cb)
{
	_on_close_cb = cb;
}

void EpollPoller::waitEpollfd(){

    int nready;
    do{
        nready = ::epoll_wait(_epfd, &(*_event_list.begin()), _event_list.size(), 100000000);
    }while(-1 == nready && errno == EINTR);

    if(-1 == nready){
        perror("epoll_wait error");
		exit(EXIT_FAILURE);
    }else if(0 == nready){
		printf("epoll_wait timeout\n");	
    }else{
        if(nready == static_cast<int>(_event_list.size())){
            _event_list.resize(_event_list.size() * 2);
        }

        for(int i = 0; i < nready; ++i){
            if(_event_list[i].data.fd == _listenfd){
                handleConnection();
            }else if(_event_list[i].data.fd == _evfd){
                handleRead();
                cout << "dopendingfunctor" <<endl;
                doPendingFunctors();
            }else{
                if(_event_list[i].events & EPOLLIN){
                    handleMessage(_event_list[i].data.fd);
                }
            }
        }
    }
}

void EpollPoller::handleConnection(){
    int cli_fd = _acceptor.acceptor();

    addEpollReadFd(_epfd, cli_fd);
    TcpConnectionPtr conn(new TcpConnection(cli_fd, this));
    // conn->sendX("welcome to server");
    conn->setConnectionCallback(_on_connection_cb);
    conn->setMessageCallback(_on_message_cb);
    conn->setCloseCallback(_on_close_cb);
    
    std::pair<ConnectionMap::iterator, bool> ret;
	ret = _conn_map.insert(std::make_pair(cli_fd, conn));
	assert(ret.second == true);
	(void)ret;

    conn->handleConnectionCallback();
}


void EpollPoller::handleMessage(int cli_fd){
    bool is_closed = isConnClosed(cli_fd);
    ConnectionMap::iterator it = _conn_map.find(cli_fd);
    assert(it != _conn_map.end());

    if(is_closed){
        it->second->handleCloseCallback();
		delEpollReadFd(_epfd, cli_fd);
		_conn_map.erase(it);
    }else{
        it->second->handleMessageCallback();
    }
}

void EpollPoller::doPendingFunctors(){
    std::vector<Functor> tmp;
    {    
        MutexLockGuard mlg(_mutex);
        tmp.swap(_pending_functors);
    }
    for(auto& functor : tmp){
        functor();
    }
}

void EpollPoller::handleRead(){

    uint64_t many;
    int ret = read(_evfd, &many, sizeof(many));
    if(ret != sizeof(many)){
        perror("read many error");
    }
}

void EpollPoller::wakeup(){
    uint64_t many = 1;
    int ret = write(_evfd, &many, sizeof(many));
    if(ret != sizeof(many)){
        perror("write many error");
    }
}



