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


void MySum(string s,promise<int> myPromise)
{
    lock_guard<shared_mutex>lg(sm);
    int addSum{};
    
    //cout << endl << "Start summation ..."<< endl;
    for(int i=1;i<=10;++i)
    {   
        v[i] = i;
        addSum += v[i];
    }
    cout << endl;
    cout << "In "<<this_thread::get_id()<<" ("<<s<<") thread : myPromise = "<< addSum << endl;
    myPromise.set_value(addSum);

}




int main()
{
    cout<<"Main Thread Starts..."<<endl;
    promise<int> myPromise;
    future<int> myFuture = myPromise.get_future();
    thread t1(MySum,"W",std::move(myPromise));
    cout<<"In Main thread : myFuture = "<<myFuture.get();
   
    if(t1.joinable())
        t1.join();


    return 0;
}
