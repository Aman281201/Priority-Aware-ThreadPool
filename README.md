# Priority-Aware Thread Pool (C++)

Built as an exercise to understand job scheduling patterns in systems, this project implements a thread pool with priority order from scratch using C++11/14/17 primitives. This implementation allows tasks to jump the line based on a priority level.

## The Idea
Not all jobs are created equal. Some tasks need to be handled immediately, while others can wait. This project explores how to manage a fixed set of worker threads that pick the most important work based on the priority.

## How it Works

The project is split into two core components:

### 1. The `Task` Class
This is a simple wrapper for the work to be done. It stores:
* **A name:** For tracking and debugging.
* **The function:** Stored as a `std::function<void()>`.
* **Priority:** An integer where **lower numbers indicate higher priority**. 

By defining how tasks compare to one another, the priority queue in the pool can automatically keep the most urgent task at the very top of the pile.

### 2. The `ThreadPool` Class
This is the orchestrator. When you initialize the pool, it starts a fixed number of worker threads.

* **Synchronization:** I used a `std::mutex` to ensure that multiple threads don't try to grab the same task at the same time. 
* **The Wait Mechanism:** Instead of having threads constantly checking for work, I used a `std::condition_variable`. Threads go to sleep when the queue is empty and are notified only when a new task is added or the pool is shutting down.

* **The Worker Loop:** Each thread runs an infinite loop that waits for a signal, pops the highest-priority task, and executes it.
* **Graceful Shutdown:** The destructor sets a `stop` flag and notifies all threads. The threads then finish any remaining tasks in the queue before joining back to the main thread.

## Building and Running

Since this uses standard C++ threads, you can compile it with any modern compiler (GCC, Clang, or MSVC).

```bash
g++ -std=c++17 main.cpp -o threadpool -lpthread
./threadpool