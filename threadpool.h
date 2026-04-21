#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class ThreadPool {
private: 
    queue<function<void()>> task_queue;
    vector<thread> threads;
    mutex queue_lock;
    condition_variable cv;
    bool stop;

public:
    ThreadPool(int size) {
        this->stop = false;
        for(int i = 0; i < size; i++) {
            threads.push_back(thread([this](){
                for(;;) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lk(this->queue_lock);
                        cv.wait(lk, [this](){ 
                            return this->stop || !this->task_queue.empty(); 
                        });

                        if(this->stop && this->task_queue.empty()) return;
                        
                        task = move(this->task_queue.front());
                        this->task_queue.pop();
                    }
                    task();
                }
            }));
        }
    }

    void add_task(function<void(vector<int>)> task_func, vector<int> args) {
        {
            unique_lock<mutex> lk(this->queue_lock);
            if(stop) return;
            task_queue.push([task_func, args](){ task_func(args); });
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lk(this->queue_lock);
            stop = true;
        }
        cv.notify_all();
        for(thread &t : threads) {
            t.join();
        }
    }
};

#endif
