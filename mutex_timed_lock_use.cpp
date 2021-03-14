#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

static int addmoney = 0;
timed_mutex mt;

void increment(int i)
{

        if(mt.try_lock_for(chrono::seconds(4)))
        {
            cout << "Thread "<< this_thread::get_id() << " get the lock and start working." << endl;
            addmoney += i;
            cout << addmoney <<" "<<endl;
           // this_thread::sleep_for(chrono::seconds(2));
            this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(2));
            mt.unlock();
        }
        else
        {
            cout << "Thread "<< this_thread::get_id() << "don't get the lock." << endl;
        }
}


int main() { 
    int money = 100;
    int more_money = 200;
	thread t1(increment,ref(money));
	thread t2(increment,ref(more_money));

    if(t1.joinable())
		t1.join();
	if(t2.joinable())
		t2.join();
	return 0;
}