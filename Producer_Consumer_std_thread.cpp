#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <future>
using namespace std;

static int arr[10]{'\0'};
mutex mt;
condition_variable cv;
bool full = false;

void Producer(string s)
{
    unique_lock<mutex>ul(mt);
    for(int i=0;i<10;++i)
        arr[i] = i;
    full = true;
    cout << "Producer produced..." << endl;
    cv.notify_all();
}

void Consumer(string s)
{
    unique_lock<mutex>ul(mt);
    cv.wait(ul,[](){return ((full) ? true : false );});
    for(auto i : arr)
    {
        cout << "Consumer consumes " << arr[i] << endl;
        arr[i] = '\0';
    }
    full = false;
}

int main()
{
    thread t1(Producer,"T1");
    thread t2(Consumer,"T2");
    cout<<"Main Thread"<<endl;
    if(t1.joinable())
        t1.join();
    if(t2.joinable())
        t2.join();

    return 0;
}
