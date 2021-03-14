#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class Moni
{
	public:
	void operator ()(int i)
	{
		cout<<"Moni's Functor : "<< i << endl;
	}

	void GetKurti(int j)
	{
		cout << "I have ordered " <<j<< " kurties from AJIO.com" <<endl;
	}

	static void GetSandals(int j)
	{
		cout << "I have ordered " <<j<< " sandals." <<endl;
	}
};

void printCount(int i)
{
	for (int j=0;j<i;++j)
		cout << "Thread " << this_thread::get_id() << " prints : " << j << " " << endl;
}

void printLambda(int i)
{
	for (int j=0;j<i;++j)
		cout << "Thread " << this_thread::get_id() << " prints : " << j << " " << endl;
}

int main() {
	thread t1(printCount,10);
	Moni m;
	if(t1.joinable())
		t1.join();
	thread t2(Moni(),10);
	if(t2.joinable())
		t2.join();
	thread t3(&Moni::GetKurti,&m,10);
	if(t3.joinable())
		t3.join();
	thread t4(&Moni::GetSandals,10);
	if(t4.joinable())
		t4.detach();//t4.join(); Now t4 output is not visible on console until main thread sleep after detaching it.
    this_thread::sleep_for(chrono::seconds(5));
	thread t5([](int x){for (int j=0;j<x;++j)
		cout << "Thread " << this_thread::get_id() << " prints : " << j << " " << endl;},10);
	if(t5.joinable())
		t5.join();
	return 0;
}
