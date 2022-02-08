#ifndef __TIMERTHREAD_H__
#define __TIMERTHREAD_H__

#include <functional>

#include "./timer.h"
#include "./thread.h"

class TimerThread{
public:
    using TimerCallback = std::function<void()>;
    TimerThread(int, int, TimerCallback &&cb);
    ~TimerThread();

    void start();
    void stop();

private:
    Timer _timer;
    Thread _sub_thread;
    bool _isstart;

};


#endif
