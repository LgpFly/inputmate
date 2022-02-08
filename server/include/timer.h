#ifndef __TIMER_H__
#define __TIMER_H__

#include <functional>

class Timer{

public:
    using TimeCallback = std::function<void()>;

    Timer(int initia_time, int interval_time, TimeCallback && cb);

    ~Timer();
    void start();
    void stop();

private:
    int creatTimeFd();
    void setTimeFd(int initia_time, int interval_time);
    void handleRead();


private:
    int _fd;
    int _initia_time;
    int _interval_time;
    TimeCallback _cb;
    bool _isstart;

};

#endif
