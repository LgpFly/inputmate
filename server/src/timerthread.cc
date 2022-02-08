#include "../include/timerthread.h"

TimerThread::TimerThread(int initia_time, int interval_time, TimerCallback && cb)
    :_timer(initia_time, interval_time, std::move(cb)), 
     _sub_thread(std::bind(&Timer::start, &_timer)), 
     _isstart(false)
{}

TimerThread::~TimerThread(){
    if(_isstart){
        stop();
    }
}


void TimerThread::start(){
    _sub_thread.start(0);
    _isstart = true;
}

void TimerThread::stop(){
    if(_isstart){
        _timer.stop();
        _sub_thread.join();
        _isstart = false;
    }
}

