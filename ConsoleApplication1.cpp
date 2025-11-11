#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int n = 100000000;
int a[n];

void do_work() {
	double x; 
	for (int i = 0; i < 10000000; i++)
		x = sin(3.1415);
}

long sum() {
	long res = 0;
	for (int i = 0; i < 100000000; i++)
	{
		res += a[i];
	}
	return res;
}

void sum1(int from, int to, long long&s) {
	long long res = 0;
	for (int i = from; i < to; i++)
		s += a[i];
}

int main()
{
	long long s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	int f0 = 0, t0 = n / 4 - 1, f1 = n / 4, t1 = n / 2 - 1, f2 = n / 2, t2 = n - n / 2 - 1, f3 = n - n / 2, t3 = n;

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 10;
	}

	auto m0 = high_resolution_clock::now();

	thread first(sum1, f0, t0, std::ref(s1));
	thread second(sum1, f1, t1, std::ref(s2));
	thread third(sum1, f2, t2, std::ref(s3));
	thread fourth(sum1, f3, t3, std::ref(s4));

	auto m1 = high_resolution_clock::now();
	
	cout << duration_cast<microseconds>(m1 - m0).count() << " microsec\n";
}