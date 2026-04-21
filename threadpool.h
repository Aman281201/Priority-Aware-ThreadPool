#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <string>
#include <iostream>

using namespace std;

class Task {
public:
    string name;
    int priority;
    function<void()> func;

    Task(string n, int p, function<void()> f) : name(n), priority(p), func(f) {}

    // lower priority number means higher task priority.
    bool operator<(const Task& other) const {
        return priority > other.priority;
    }
};

class ThreadPool {
private: 
    priority_queue<Task> task_queue;
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
                    function<void()> task_func;
                    {
                        unique_lock<mutex> lk(this->queue_lock);
                        cv.wait(lk, [this](){ 
                            return this->stop || !this->task_queue.empty(); 
                        });

                        if(this->stop && this->task_queue.empty()) return;
                        
                        task_func = move(this->task_queue.top().func);
                        this->task_queue.pop();
                    }
                    task_func();
                }
            }));
        }
    }

    void add_task(string name, int priority, function<void(vector<int>, string)> task_func, vector<int> args) {
        {
            unique_lock<mutex> lk(this->queue_lock);
            if(stop) return;
            
            cout << "Enqueuing task: " << name << " (Priority: " << priority << ")" << endl;
            
            task_queue.push(Task(name, priority, [task_func, args, name](){ 
                task_func(args, name); 
            }));
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
