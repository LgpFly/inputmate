#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>

#include "./nocopyable.h"
#include "./mutexlock.h"

class Condition
:Nocopyable
{
public:
    Condition(MutexLock& mtx)
        :_mutex(mtx)
    {
        pthread_cond_init(&_cond, NULL);
    }


    ~Condition(){
        pthread_cond_destroy(&_cond);
    }

    void wait(){
        pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
    }

    void notify(){
        pthread_cond_signal(&_cond);
    }

    void notifyAll(){
        pthread_cond_broadcast(&_cond);
    }

private:
    pthread_cond_t _cond;
    MutexLock & _mutex;
};



#endif


