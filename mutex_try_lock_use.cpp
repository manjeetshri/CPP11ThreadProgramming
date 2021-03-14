#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

static int count = 0;
mutex m1;

void printNumbers1to1000()
{
    //if(m1.try_lock())
    //{
        for(int i=0;i<100;++i)
        {

            //cout<<"Thread "<<this_thread::get_id()<<" get the lock and start sleeping."<<endl;
            //this_thread::sleep_for(chrono::seconds(2));
            //cout<<"Thread "<<this_thread::get_id()<<" start working."<<endl;
            if(m1.try_lock())
            {
                cout << ++count <<" "<<endl;
                
            }
            m1.unlock();
        }   
    //}
    //m1.unlock();
}


int main() {
	thread t1(printNumbers1to1000);
	thread t2(printNumbers1to1000);

    if(t1.joinable())
		t1.join();
	if(t2.joinable())
		t2.join();
	return 0;
}
