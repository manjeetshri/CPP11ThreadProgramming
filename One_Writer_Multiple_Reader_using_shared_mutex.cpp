#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <vector>
using namespace std;

int v[10];
shared_mutex sm;
condition_variable cv;


void Writer(string s)
{
    lock_guard<shared_mutex>lg(sm);
    //sm.lock();
    cout << "Writer starts writing."<< endl;
    for(int i=0;i<10;++i)
    {   
        v[i] = i;
        cout << v[i] << endl;
    }
    cout << "Writer finishes writing."<< endl;
    //sm.unlock();
}

void Reader(string s)
{
    sm.lock_shared();
    this_thread::sleep_for(chrono::seconds(3));
    for(auto i : v)
    {   
        cout << "Reader reads "<<"("<<s<<") : "<<v[i]<< endl;
    }
    sm.unlock_shared();
}


int main()
{
    cout<<"Main Thread Starts..."<<endl;
    thread t1(Writer,"W");
    thread t2(Reader,"R1");
    thread t3(Reader,"R2");

    if(t1.joinable())
        t1.join();
    if(t2.joinable())
        t2.join();
    if(t3.joinable())
        t3.join();

    return 0;
}
