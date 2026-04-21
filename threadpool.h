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
vector<jthread> threads;
mutex queue_lock;
condition_variable cv;
bool stop;

public:
int size;

ThreadPool(int size) {
  this->stop = false;
  for(int i = 0; i < size; i++)
    {
      threads.push_back(jthread([this](){
        for(;;)
          {
            function<void()>task;
            {
              unique_lock<mutex> lk(this->queue_lock);
              cv.wait(lk,
                [this](){ 
                return this->stop || this->task_queue.size() > 0;
              });

              //gracious exit
              if(this->stop && this->task_queue.size() == 0)
                return;
              
              task = task_queue.move(this->task_queue.front());
              task_queue.pop();
            }

            task();
          }
      })
    }
};

void enqueue() {
  
}

~ThreadPool()
{
  
}

void add_task(task t)
{
  
}

}