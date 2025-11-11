#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <cmath>
#include <chrono>
#include <ctime>
#include <cstdlib>



using namespace std;
using namespace std::chrono;

struct Person {
	int mushrooms;
	double x, y;
	double dist;
};

const double U = 1, T = 1, Tmin = T * 1000;

double Distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2-x1, 2) + pow(y2 - y1, 2));
}

double rd() {
	return rand() / (double)RAND_MAX;
}

void mush(int id, promise<Person>& my_promise, future<Person>& friend_future) {
	srand(time(nullptr) + id);

	double x = 0, y = 0, path = 0, sumD = 0, sumF = 0;
	int steps = 0, mushs = 0;

	while (true) {
		double angle = rd() * 2 * M_PI;
		double speed = rd() * U;
	}
}


int main()
{
	srand(time(nullptr));

	promise<Person> p1, p2;
	future<Person> f1 = p1.get_future();
	future<Person> f2 = p2.get_future();

	future<void> pk1 = async(launch::async, mush, 1, ref(p1), ref(f2));
	future<void> pk2 = async(launch::async, mush, 2, ref(p2), ref(f1));

	pk1.get();
	pk2.get();
}