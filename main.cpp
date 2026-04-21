#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include "threadpool.h"

// task function 1
void add_task_func(vector<int> input, string task_name) {

    cout<<"Executing task : "<< task_name<<endl;
    int sum = 0;
    for(int n: input)
    sum += n;

    this_thread::sleep_for(chrono::milliseconds(10));
    cout << "Sum: " << sum << endl;
}

// task function 2
void multiply_task_func(vector<int> input, string task_name) {
    cout<<"Executing task : "<<task_name<<endl;
    int prod = 1;
    for(int n : input) prod *= n;

    this_thread::sleep_for(chrono::milliseconds(10));
    cout << "Product: " << prod << endl;
}

int main() {
    ThreadPool pool(2);

    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {4, 5, 6};

    pool.add_task("T#1", 1, add_task_func, v1);
    pool.add_task("T#2", 9, multiply_task_func, v1);
    pool.add_task("T#3", 8, add_task_func, v2);
    pool.add_task("T#4", 7, multiply_task_func, v2);
    pool.add_task("T#5", 6, add_task_func, v1);
    pool.add_task("T#6", 5, multiply_task_func, v1);
    pool.add_task("T#7", 4, add_task_func, v2);
    pool.add_task("T#8", 3, multiply_task_func, v2);

    this_thread::sleep_for(chrono::milliseconds(200));

    return 0;
}
