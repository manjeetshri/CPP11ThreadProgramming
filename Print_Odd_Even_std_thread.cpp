#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <future>
using namespace std;

static int arr[20]{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
mutex mt;
condition_variable cv;
bool done = false;

void IsNumberOdd(string s,int size)
{
    unique_lock<mutex>ul(mt);
    for(auto i : arr)
    {   
        if(i % 2 != 0)
            cout << "Number " <<i<<" is odd."<< endl;
    }
    done = true;
    cv.notify_all();
}

void IsNumberEven(string s,int size)
{
    unique_lock<mutex>ul(mt);
    cv.wait(ul,[](){return ((done) ? true : false );});
    for(auto i : arr)
    {
        if(i % 2 == 0)
            cout << "Number " <<i<<" is even."<< endl;
    }
    done = false;
}

int main()
{
    int size = sizeof(arr)/sizeof(arr[0]);
    thread t1(IsNumberOdd,"T1",ref(size));
    thread t2(IsNumberEven,"T2",ref(size));
    cout<<"Main Thread"<<endl;
    if(t1.joinable())
        t1.join();
    if(t2.joinable())
        t2.join();

    return 0;
}
