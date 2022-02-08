#ifndef __SOCKETUTIL_H__
#define __SOCKETUTIL_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/eventfd.h>
#include <sys/epoll.h>


inline int creatSockFd(){
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == fd){
        perror("create socket fd");
    }
    return fd;
}

inline void setNonblock(int fd){
    int flag = ::fcntl(fd, F_GETFL, 0);
    flag |= O_NONBLOCK;
    ::fcntl(fd, F_SETFL, 0);
}

inline int creatEpollFd(){
    int epfd = ::epoll_create1(0);
    if(-1 == epfd){
        perror("epoll create1");
    }
    return epfd;
}

inline int creatEventFd(){
    int evfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(-1 == evfd){
        perror("eventfd error");
    }
    return evfd;
}

inline void addEpollReadFd(int epfd, int fd){
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    if(-1 == ret){
        perror("read fd epoll add");
        exit(EXIT_FAILURE);
    }

}

inline void delEpollReadFd(int epfd, int fd){
    struct epoll_event ev;
    ev.data.fd = fd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
    if(-1 == ret){
        perror("del fd error");
        exit(EXIT_FAILURE);
    }
}

inline size_t recvPeek(int sockfd, void* buf, size_t len){
    int nread;
    do{
        nread = ::recv(sockfd, buf, len, MSG_PEEK);
    }while(-1 == nread && errno == EINTR);
    return nread;
}

inline bool isConnClosed(int sockfd){
    char buf[1024];
    int nread = recvPeek(sockfd, buf, sizeof(buf));
    if(-1 == nread){
        perror("recvpeek");
        return true;
    }

    return (0 == nread);
}


#endif
