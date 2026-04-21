#include <iostream>
#include <vector>
#include <numeric>
#include "threadpool.h"

// task function 1
void add_task_func(vector<int> input) {
    int sum = 0;
    for(int n: input)
    sum += n;

    cout << "Sum: " << sum << endl;
}

// task function 2
void multiply_task_func(vector<int> input) {
    int prod = 1;
    for(int n : input) prod *= n;

    cout << "Product: " << prod << endl;
}

int main() {
    ThreadPool pool(3);

    // inputs
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {10, 20, 30};

    pool.add_task(add_task_func, v1);
    pool.add_task(multiply_task_func, v1);
    pool.add_task(add_task_func, v2);
    pool.add_task(multiply_task_func, v2);

    this_thread::sleep_for(chrono::milliseconds(100));

    return 0;
}
