#include <unistd.h>
#include <iostream>
#include "../include/thread.h"
#include "../include/threadpool.h"

void ThreadPool::start(){
    for(int i = 0; i < _thread_num; ++i){
        shared_ptr<Thread> p_thread(new Thread(std::bind(&ThreadPool::threadFunc, this)));
        _threads.push_back(p_thread);
    }
    int num = 0;
    for(auto& p_thread : _threads){
        p_thread->start(num);
        ++num;
    }
}

void ThreadPool::stop(){
    if(!_is_exit){
        while(!_task_que.empty()) {
			::sleep(1);
			cout << ">>> Threadpool sleep 1 s" << endl;
		}

		_is_exit = true;
		cout << ">>> Threadpool -> stop: _is_exit = " << _is_exit << endl;

		_task_que.wakeup();

		for(auto & pthread : _threads) {
			pthread->join();
		}
    }
}

ThreadPool::~ThreadPool()
{
	if(!_is_exit) {
		stop();
	}
}


void ThreadPool::addTask(Task && task){
    _task_que.push(std::move(task));
}

Task ThreadPool::getTask(){
    return _task_que.pop();
}

void ThreadPool::threadFunc(){
    while(!_is_exit){
        Task task = getTask();
        // std::cout << "run this threadpool::threadfunc" << std::endl;
        // if(NULL == task){
        //     std::cout << "task is null" << endl;
        // }
        
        if(task){
            std::cout << "run this threadpool::threadfunc" << std::endl;
            std::cout << "执行Task" << endl;
            task();
        }
    }
}
