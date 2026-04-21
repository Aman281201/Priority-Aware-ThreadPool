#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

void function()
{
    for(int i = 0; i < 1000; i++)
    cout<<"|";
}

void function2()
{
    for(int i = 0; i < 1000; i++)
    cout<<"-";
}


int main() {
    cout<<"start"<<endl;
    thread w1(function);
    thread w2(function2);
    cout<<"aman";
    w2.join();

    w1.join();

    
    return 0;
}
