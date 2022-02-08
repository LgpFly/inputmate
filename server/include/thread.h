#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

#include "./nocopyable.h"

using std::function;

class Thread;

struct ThreadPtr{
    int _number;
    Thread *_pthread;
};


class Thread
:Nocopyable{

    using ThreadCallback = function<void()>;

public:
    Thread(ThreadCallback && cb);
    ~Thread();

    void start(int number);
    void join();

    bool isRuning() const {return _isruning;}

private:
    static void* threadFunc(void*);

private:
    pthread_t _pid;
    bool _isruning;
    ThreadCallback _cb;
};



#endif
