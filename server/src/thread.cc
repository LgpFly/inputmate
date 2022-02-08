#include <iostream>

#include "../include/thread.h"

using std::cout;
using std::endl;


__thread int t_num;

Thread::Thread(ThreadCallback && cb)
    :_pid(0), _isruning(false), _cb(std::move(cb))
{
    cout << "Thread(cb)" << endl;
}

void Thread::start(int number){
    
    ThreadPtr * threadPtr = new ThreadPtr();
    threadPtr->_number = number;
    threadPtr->_pthread = this;
    pthread_create(&_pid, NULL, threadFunc, threadPtr);
    _isruning = true;
}

void* Thread::threadFunc(void *arg){
    ThreadPtr* threadPtr = static_cast<ThreadPtr*>(arg);
    Thread* pthread = threadPtr->_pthread;
    t_num = threadPtr->_number;
    if(pthread){
        cout << "接下来要去取任务了" << endl;
        pthread->_cb();
    }
    delete threadPtr;
}

void Thread::join(){
    pthread_join(_pid, NULL);
    _isruning = false;
}

Thread::~Thread(){
    if(_isruning){
        pthread_detach(_pid);
        _isruning = false;
    }

    cout << "Thread()" << endl;
}
