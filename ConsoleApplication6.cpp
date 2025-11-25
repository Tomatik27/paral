#include <iostream>
#include <omp.h>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

void Bubble2(int Mass[], int n) {
	int i, j;
	for (i = 0; i < n; i++){
		if (i % 2 == 0) {
			for (j = 0; j < n - 1; j += 2){
				if (Mass[j] > Mass[j + 1]) swap(Mass[j], Mass[j + 1]);
			}
		}
		else{
			for (j = 0; j < n - 1; j += 2){
				if (Mass[j] > Mass[j + 1]) swap(Mass[j], Mass[j + 1]);
			}
		}
	}
}

void Bubble4(int Mass[], int n) {
	int i, j;
#pragma omp parallel default(none) shared(Mass, n) private(i)
	for (i = 0; i < n; i++){
		if (i % 2 == 0) {
#pragma omp for
			for (j = 0; j < n - 1; j += 2){
				if (Mass[j] > Mass[j + 1]) swap(Mass[j], Mass[j + 1]);
			}
		}
		else{
#pragma omp for
			for (j = 0; j < n - 1; j += 2){
				if (Mass[j] > Mass[j + 1]) swap(Mass[j], Mass[j + 1]);
			}
		}
	}
}



int main()
{
	const int n = 100;

	int* Mass_1 = new int[n];
	for (int i = 0; i < n; i++) {
		Mass_1[i] = rand() % 100;
	}

	int* Mass_2 = new int[n];
	for (int i = 0; i < n; i++){
		Mass_2[i] = rand() % 100;
	}

	auto t0 = chrono::high_resolution_clock::now();
	Bubble2(Mass_1, n);
	auto t1 = chrono::high_resolution_clock::now();

	cout << "even-odd bubble sort: " << chrono::duration_cast<chrono::microseconds>(t1 - t0).count() << '\n';

	t0 = chrono::high_resolution_clock::now();
	Bubble4(Mass_2, n);
	t1 = chrono::high_resolution_clock::now();

	cout << "omp bubble sort: " << chrono::duration_cast<chrono::microseconds>(t1 - t0).count() << '\n';

}