#include <iostream>
#include <Windows.h>

using namespace std;

#define ITERATION_COUNT 10000000

double PerformanceFrequency = 0.0;
__int64 CounterStart = 0;

void StartCounter() {
	LARGE_INTEGER performanceCount;

	if (!QueryPerformanceFrequency(&performanceCount))
		cout << "QueryPerformanceFrequency failed!" << endl;

	PerformanceFrequency = double(performanceCount.QuadPart) / 1000.0;

	QueryPerformanceCounter(&performanceCount);

	CounterStart = performanceCount.QuadPart;
}

double GetCounter() {
	LARGE_INTEGER performanceCount;

	QueryPerformanceCounter(&performanceCount);

	return double(performanceCount.QuadPart - CounterStart) / PerformanceFrequency;
}

struct Object {
	int a;
	int b;
	int c;

	int Foo() {
		return a + b + c;
	}
};

struct FragmentedObject {
	int a;
	char f1[64];
	int b;
	char f2[128];
	int c;
	char f3[256];
	int d;

	int Foo() {
		d = a + b + c;

		return d;
	}
};

struct DerivedObject : Object {
	char o1[64];
	char o2[128];
	char o3[256];
};

int Foo(int a, int b, int c) {
	return a + b + c;
}

int main() {
	auto a = new int[ITERATION_COUNT];
	auto b = new int[ITERATION_COUNT];
	auto c = new int[ITERATION_COUNT];
	auto o = new struct Object[ITERATION_COUNT];
	auto f = new struct FragmentedObject[ITERATION_COUNT];
	auto d = new struct DerivedObject[ITERATION_COUNT];

	// DOD
	StartCounter();

	for (int i = 0; i < ITERATION_COUNT; ++i) {
		Foo(a[i], b[i], c[i]);
	}

	cout << GetCounter() << " (DOD, per array of data iterations, perfect utilization)" << endl;

	// OOD
	StartCounter();

	for (int i = 0; i < ITERATION_COUNT; ++i) {
		o[i].Foo();
	}

	cout << GetCounter() << " (OOD, per structure of data iterations, perfect utilization)" << endl;

	// OOD (Fragmented)
	StartCounter();

	for (int i = 0; i < ITERATION_COUNT; ++i) {
		f[i].Foo();
	}

	cout << GetCounter() << " (OOD, per structure of data iterations, fragmented utilization)" << endl;

	// OOP (Inheritance)
	StartCounter();

	for (int i = 0; i < ITERATION_COUNT; ++i) {
		d[i].Foo();
	}

	cout << GetCounter() << " (OOP, per structure of data iterations, derived utilization)" << endl;

	delete[] a;
	delete[] b;
	delete[] c;
	delete[] o;
	delete[] f;
	delete[] d;
}
