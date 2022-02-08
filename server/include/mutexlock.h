#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>

#include "./nocopyable.h"

class MutexLock
:Nocopyable
{
public:
    MutexLock(){
        pthread_mutex_init(&_mutex, NULL);
    }

    ~MutexLock(){
        pthread_mutex_destroy(&_mutex);
    }

    void lock(){
        pthread_mutex_lock(&_mutex);
    }

    void unlock(){
        pthread_mutex_unlock(&_mutex);
    }

    pthread_mutex_t * getMutexLockPtr(){
        return &_mutex;
    }

private:
    pthread_mutex_t _mutex;
};


class MutexLockGuard{
public:
    MutexLockGuard(MutexLock & mtx)
    :_mutex(mtx)
    {
        _mutex.lock();
    }

    ~MutexLockGuard(){
        _mutex.unlock();
    }

private:
    MutexLock & _mutex;
};



#endif
