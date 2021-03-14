#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

static int ms = 0;
mutex m1;


void printLambda(int i)
{
	m1.lock();
	for (int j=0;j<i;++j)
		cout << "Thread " << this_thread::get_id() << " prints : " << ms++ << " " << endl;
	m1.unlock();

}

int main() {
	thread t1(printLambda,10);
	thread t2(printLambda,10);

    if(t1.joinable())
		t1.join();
	if(t2.joinable())
		t2.join();
	return 0;
}
