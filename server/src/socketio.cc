#include "../include/socketio.h"
#include "../include/socketutil.h"

SocketIo::SocketIo(int sockfd)
    :_sockfd(sockfd)
{}

size_t SocketIo::readn(char* buf, size_t count){
    size_t nleft = count;
    char *p_buf = buf;
    size_t one_read;
    while(nleft > 0){
        one_read = ::read(_sockfd, p_buf, nleft);
        if(-1 == one_read){
            if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
        }else if(0 == one_read){
            break;
        }else{
            p_buf += one_read;
            nleft -= one_read;
        }
    }
    return (count - nleft);
}

size_t SocketIo::writen(const char* buf, size_t count){
    
    int nleft = count;
    const char* p_buf = buf;
    int one_write;
    while(nleft > 0){
        one_write = ::write(_sockfd, p_buf, nleft);
        if(-1 == one_write){
            if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
        }else{
            nleft -= one_write;
            p_buf += one_write;
        }
    }

    return (count - nleft);
}

size_t SocketIo::recvPeek(char* buf, size_t count){
    int nread;

    do{
        nread = ::recv(_sockfd, buf, count, MSG_PEEK);
    }while(-1 == nread && errno == EINTR);

    return nread;
}

size_t SocketIo::readLine(char* buf, size_t max_len){
    size_t nleft = max_len - 1;
    char* p_buf = buf;
    size_t total = 0;
    int one_read;
    while(nleft > 0){
        one_read = recvPeek(p_buf, nleft);

        if(one_read <= 0){
            return one_read;
        }

        for(int i = 0; i < one_read; ++i){
            if(p_buf[i] == '\n'){
                
                size_t nsize = i + 1;
                if(readn(p_buf, nsize) != nsize){
                    return EXIT_FAILURE;
                }
                p_buf += nsize;
                *p_buf = 0;
                total += nsize;
                return total;
            }
        }
        if(readn(p_buf, one_read) != one_read){
            return EXIT_FAILURE;
        }

        p_buf += one_read;
        nleft -= one_read;
        total += one_read;
    }
    *p_buf = 0;
    return max_len - 1;
}

