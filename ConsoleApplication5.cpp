#include <iostream>
#include <omp.h>

using namespace std;

void Path(int*& Adj, int n) {
	int i;
	Adj = new int[n * n];
	for (i = 0; i < n * n; i++) 
		Adj[i] = 0;
	for (i = 1; i < n * n; i += n + 1) 
		Adj[i] = 1;
	for (i = n; i < n * n; i += n + 1) 
		Adj[i] = 1;
}

void Simple(int*& Adj, int n) {
	int i;
	Adj = new int[n * n];
	for (i = 0; i < n * n; i++) 
		Adj[i] = 0;
	for (i = 1; i < n * n; i += n + 1) 
		Adj[i] = 1;
	for (i = n; i < n * n; i += n + 1) 
		Adj[i] = 1;
	Adj[n - 1] = 1;
	Adj[n * (n - 1)] = 1;

}

void OrientInc(int*& Adj, int n) {
	int i;
	Adj = new int[n * n];

	for (i = 0; i < n * n; i++) Adj[i] = 0;

	for (i = 1; i < n * n; i += n + 1) Adj[i] = 1;
	for (i = n; i < n * n; i += n + 1) Adj[i] = 0;
}

void OrientDec(int*& Adj, int n) {
	int i;
	Adj = new int[n * n];

	for (i = 0; i < n * n; i++) Adj[i] = 0;

	for (i = 1; i < n * n; i += n + 1) Adj[i] = 0;
	for (i = n; i < n * n; i += n + 1) Adj[i] = 1;
}

void Compl(int*& Adj, int n) {
	int i;
	Adj = new int[n * n];

	for (i = 0; i < n * n; i++) Adj[i] = 1;
	for (i = 0; i < n * n; i += n + 1) Adj[i] = 0;
}

int Min(int x, int y) {
	int Result = (x < y) ? x : y;
	
	if ((x == 0) && y > 0) Result = y;
	if ((y == 0) && x > 0) Result = x;
	if ((y == 0) && (x == 0)) Result = 0;

	return Result;
}

void ParallelFloyd(int* pMatrix, int Size) {
	int t1, t2;
	for (int k = 0; k < Size; k++)
		#pragma omp parallel for private (t1, t2)
			for (int i = 0; i < Size; i++)
				for (int j = 0; j < Size; j++)
					if ((pMatrix[i * Size + k] != 0) && (pMatrix[k * Size + j] != 0)) {
						t1 = pMatrix[i * Size + j];
						t2 = pMatrix[i * Size + k] + pMatrix[k * Size + j];
						pMatrix[i * Size + j] = Min(t1, t2);
					}
}

int main()
{
	int* Adj;
	int i, j, n;
	cout << "Num: ";
	cin >> n;

	Path(Adj, n);
	OrientInc(Adj, n);
	OrientDec(Adj, n);
	Simple(Adj, n);

	ParallelFloyd(Adj, n);

	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
			cout << Adj[j * n + i];
		cout << '\n';
	}
}