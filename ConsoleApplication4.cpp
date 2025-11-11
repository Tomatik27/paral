#include<iostream>
#include<thread>
#include<omp.h>
#include<future>
#include<chrono>

using namespace std;
using namespace std::chrono;

int main()
 {

	int i, j;
	const int n = 300;
	long long sum = 0;
	int Matrix[n][n];
	int Matrix1[n][n];
	cout << sum + sum <<"\n\n\n\n";
	for (i = 0; i < n; i++) 
		for (j = 0; j < n; j++) { 
			Matrix[i][j] = 1; 
			Matrix1[i][j] = 1; 
		}

	auto start = high_resolution_clock::now();
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			sum += Matrix[i][j] + Matrix1[i][j];
	
	auto middle = high_resolution_clock::now();

	cout << sum << '\n';

	sum = 0;
	
	auto middle2 = high_resolution_clock::now();

#pragma omp for
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum += Matrix[i][j];
			sum += Matrix1[i][j];
		}
	}

	auto end = high_resolution_clock::now();
	cout << sum << "\n\n";
	cout << duration_cast<nanoseconds>(middle - start).count() << '\n';
	cout << duration_cast<nanoseconds>(end - middle2).count() << '\n';

}