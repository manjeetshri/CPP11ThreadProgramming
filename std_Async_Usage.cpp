#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <vector>

using namespace std;

int v[10]{'\0'};
shared_mutex sm;
condition_variable cv;


int * MySum(string s)
{
    lock_guard<shared_mutex>lg(sm);
    int addSum{};
    
    //cout << endl << "Start summation ..."<< endl;
    for(int i=0;i<10;++i)
    {   
        v[i] = i;
        addSum += v[i];
    }
    cout << endl;
    cout << "In "<<this_thread::get_id()<<" ("<<s<<") thread  " << endl;
    return v;

}




int main()
{
    cout<<"Main Thread Starts..."<<endl;

    future<int*> myFuture = async(MySum,"T1");
    cout<<"In Main thread : myFuture = ";
   
    auto ptr = myFuture.get();
    for(int i=0;i<10;++i)
        cout<<*(ptr++)<<endl;

    return 0;
}
