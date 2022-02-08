#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include <string>
#include <memory>
#include <functional>

#include "nocopyable.h"
#include "./inetaddress.h"
#include "./socket.h"
#include "./socketio.h"

class EpollPoller;
class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection
:Nocopyable, public std::enable_shared_from_this<TcpConnection>{

public:
    typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;
    TcpConnection(int sockfd, EpollPoller* loop);
    ~TcpConnection();

    std::string receive();
    void sendX(const std::string msg);
    void sendInLoop(const std::string& msg);
    void shutdown();

    std::string toString();

    void setConnectionCallback(TcpConnectionCallback cb);
    void setMessageCallback(TcpConnectionCallback cb);
    void setCloseCallback(TcpConnectionCallback cb);

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

private:
    Socket _sockfd;
    SocketIo _sockio;
    const InetAddress _local_addr;
    const InetAddress _peer_addr;
    bool _shutdown_write;
    EpollPoller *_loop;

    TcpConnectionCallback _on_connection_cb;
    TcpConnectionCallback _on_message_cb;
    TcpConnectionCallback _on_close_cb;
};



#endif
