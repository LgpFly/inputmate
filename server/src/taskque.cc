
#include <iostream>

#include "../include/taskque.h"

using std::cout;
using std::endl;

void TaskQue::push(Task && task){
    MutexLockGuard auto_lock(_mutex);

    while(full()){
        _not_full.wait();
    }

    _que.push(std::move(task));
    cout << "size of _que:" << _que.size() <<endl; 
    _not_empty.notify();
}

Task TaskQue::pop(){

    MutexLockGuard auto_lock(_mutex);
    while(_flag && empty()){
        _not_empty.wait();
    }

    if(_flag){
        Task task = _que.front();
        _que.pop();
        cout << "size of _que:" << _que.size() <<endl; 
        _not_full.notify();
        return task;
    }else{
        return NULL;
    }
}
