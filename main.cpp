#include <numeric>
#include <algorithm>
#include <future>
#include <thread>
#include <iostream>
using namespace std;

int f(int x) {	
	this_thread::sleep_for(1s);
	return x;
}
int main(void)
{
	packaged_task<int(int)> task(f);

	auto retFut = task.get_future();

	thread(move(task), 10).detach();

	cout << "xxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	int i = 0;

	while(retFut.valid() && i < 6)
	{	
		this_thread::sleep_for(0.1s);
		cout << i << ' ';
		++i;
	}
	int value = retFut.get();
	cout << value;
	return 0;
}