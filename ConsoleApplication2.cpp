#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
using namespace std::chrono;
mutex mtx;
condition_variable cv;

int s = 0;
int a[2000];

auto t0 = high_resolution_clock::now();

void sl(int t) {
	this_thread::sleep_for(seconds (t));
	auto t1 = high_resolution_clock::now();
	cout << duration_cast<milliseconds>(t1 - t0).count() << " millisecs, ";
}

int main()
{
	for (int i = 0; i < 12; i++)
	{
		cout << '#' << i + 1 << ":\n";
		thread th1(sl, 2);
		th1.join();
		thread th2(sl, 3);
		th2.join();
		thread th3(sl, 5);
		th3.join();

		cout << "\n";
	}
}
