#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include <stdio.h>

class SocketIo{

public:
    SocketIo(int sockfd);

    size_t readn(char* buf, size_t count);
    size_t writen(const char* buf, size_t count);
    size_t readLine(char* buf, size_t max_len);

private:
    size_t recvPeek(char* buf, size_t count);

private:
    int _sockfd;
};


#endif


