#ifndef __TASKQUE_H__
#define __TASKQUE_H__

#include <queue>
#include <functional>

#include "../include/mutexlock.h"
#include "../include/condition.h"



typedef std::function<void()> Task;

class TaskQue{
public:
    TaskQue(int que_size)
        :_que_size(que_size), _mutex(), _not_full(_mutex), 
        _not_empty(_mutex), _flag(true)
    {}

    void push(Task && task);
    Task pop();

    bool empty() const{
        return 0 == _que.size();
    }
    bool full() const{
        return _que_size == _que.size();
    }

    void wakeup(){
        _flag = false;
        _not_empty.notifyAll();
    }

private:
    int _que_size;
    std::queue<Task> _que;
    MutexLock _mutex;
    Condition _not_full;
    Condition _not_empty;
    bool _flag;
};



#endif
