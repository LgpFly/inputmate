#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <vector>
#include <memory>
#include <functional>

#include "./taskque.h"
#include "./thread.h"

using namespace std;

class ThreadPool{
public:
    using Task = std::function<void()>;
    ThreadPool(int thread_num, int que_size)
        :_thread_num(thread_num), _que_size(que_size), 
        _task_que(_que_size), _is_exit(false)
    {
        _threads.reserve(_thread_num);
    }

    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task && task);

private:
    void threadFunc();
    Task getTask();


private:
    int _thread_num;
    int _que_size;
    vector<shared_ptr<Thread>> _threads;
    TaskQue _task_que;
    bool _is_exit;
};

#endif


