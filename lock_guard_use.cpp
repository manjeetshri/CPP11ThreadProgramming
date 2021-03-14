#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

static int count = 0;
mutex m1;

void printNumbers1toN(int N,string s)
{
    lock_guard<mutex>lock(m1);
    if(N<=0)
        return ;
    for(int i=0;i<N;++i)
    {
        cout << "Thread "<< this_thread::get_id() <<"("<< s << ")" <<" prints : "<< ++count <<" "<<endl;
    }
    
}

int main() {
	thread t1(printNumbers1toN,20,"T1");
	thread t2(printNumbers1toN,10,"T2");

    if(t1.joinable())
		t1.join();
	if(t2.joinable())
		t2.join();
	return 0;
}