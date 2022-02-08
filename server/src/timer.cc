#include <unistd.h>
#include <error.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <iostream>

#include "../include/timer.h"

using namespace std;

Timer::Timer(int initia_time, int interval_time, TimeCallback && cb)
    :_fd(creatTimeFd()), _initia_time(initia_time), _interval_time(interval_time), 
    _cb(move(cb)), _isstart(false)
{}

void Timer::start(){
    struct pollfd pfd;
    pfd.fd = _fd;
    pfd.events = POLLIN;

    setTimeFd(_initia_time, _interval_time);

    _isstart = true;

    while(_isstart){
        int nready = ::poll(&pfd, 1, 5000);
        if(-1 == nready && errno == EINTR){
            continue;
        }else if(-1 == nready){
            perror("poll error");
            exit(EXIT_FAILURE);
        }else if(0 == nready){
            cout << "poll timeout" << endl;
        }else{
            if(pfd.revents & POLLIN){
                handleRead();
                if(_cb){
                    _cb();
                }

            }
        }
    }
}

void Timer::stop(){
    setTimeFd(0, 0);
    if(_isstart){
        _isstart = false;
    }
}

Timer::~Timer(){
    if(_isstart){
        stop();
    }
}

int Timer::creatTimeFd(){
    int fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if(-1 == fd){
        perror("timerfd create error");
    }
    return fd;
}

void Timer::setTimeFd(int initia_time, int interval_time){
    struct itimerspec value;
    value.it_value.tv_sec = initia_time;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = interval_time;
    value.it_interval.tv_nsec = 0;
    int ret = ::timerfd_settime(_fd, 0, &value, NULL);
    if(-1 == ret){
        perror("timerfd_settimer error");
    }
}

void Timer::handleRead(){
    uint64_t many;
    int ret = ::read(_fd, &many, sizeof(uint64_t));
    if(ret = sizeof(uint64_t)){
        perror("read error");
    }
}
