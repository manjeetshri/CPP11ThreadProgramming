#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std;

static int balance = 0;
mutex m1;
condition_variable cv;

void WithdrawMoney(int N,string s)
{

    unique_lock<mutex>lockm(m1);
    cv.wait(lockm,[](){return(balance != 0)? true:false;});
    
    if(N>balance)
        cout << "Thread doesn't have enough balance because current balance is : " << balance <<" "<<endl;
    else
        {
            cout << "Thread "<< this_thread::get_id() <<"("<< s << ")" <<" withdraws : "<< N << " from " << balance <<" "<<endl;
            cout << "Remaining Balance : "<< (balance -= N) <<endl;
            ;
        }
    
}

void AddMoney(int N,string s)
{
    unique_lock<mutex>lockm(m1);
    
    cout << "Thread "<< this_thread::get_id() <<"("<< s << ")" <<" adds : "<< (balance+=N) <<" "<<endl;
    cv.notify_one();
    
}

int main() {
	thread t1(AddMoney,1000,"T1");
	thread t2(WithdrawMoney,500,"T2");

    if(t1.joinable())
		t1.join();
	if(t2.joinable())
		t2.join();
	return 0;
}
