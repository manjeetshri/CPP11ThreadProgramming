#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

static int count = 0;
recursive_mutex m1;

void printNumbers1toN(int N)
{
    if(N<=0)
        return ;
    printNumbers1toN(N-1);
     m1.lock();
    {
        cout << ++count <<" "<<endl;
                
    }
    m1.unlock();
}

/*int FactorialN(int N)
{
    int fact{};
    if(N == 1 || N == 0)
        return 1;
    fact = N * FactorialN(N-1);
    cout << "Factorial of "<<N<<" is "<<fact<<endl;
    return fact;
}*/


int main() {
	thread t1(printNumbers1toN,20);
	thread t2(printNumbers1toN,10);
    //thread t3(FactorialN,5);
    if(t1.joinable())
		t1.join();
	if(t2.joinable())
		t2.join();
	if(t3.joinable())
		t3.join();
	return 0;
}
