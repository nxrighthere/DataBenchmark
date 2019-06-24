#include <iostream>
#include <Windows.h>

using namespace std;

#define ITERATION_COUNT 10000000

double PerformanceFrequency = 0.0;
__int64 CounterStart = 0;

void StartCounter() {
	LARGE_INTEGER performanceCount;

	if (!QueryPerformanceFrequency(&performanceCount))
		cout << "QueryPerformanceFrequency failed!\n";

	PerformanceFrequency = double(performanceCount.QuadPart) / 1000.0;

	QueryPerformanceCounter(&performanceCount);

	CounterStart = performanceCount.QuadPart;
}

double GetCounter() {
	LARGE_INTEGER performanceCount;

	QueryPerformanceCounter(&performanceCount);

	return double(performanceCount.QuadPart - CounterStart) / PerformanceFrequency;
}

struct PerfectObject {
	int a;
	int b;
	int c;

	int foo() {
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

	int foo() {
		d = a + b + c;

		return d;
	}
};

int foo(int a, int b, int c) {
	return a + b + c;
}

int main() {
	auto a = new int[ITERATION_COUNT];
	auto b = new int[ITERATION_COUNT];
	auto c = new int[ITERATION_COUNT];
	auto o = new struct PerfectObject[ITERATION_COUNT];
	auto f = new struct FragmentedObject[ITERATION_COUNT];

	// DOD
	StartCounter();

	for (int i = 0; i < ITERATION_COUNT; ++i)	{
		foo(a[i], b[i], c[i]);
	}

	cout << GetCounter();
	cout << " (DOD, per array of data iterations, perfect utilization)\n";

	// OOD
	StartCounter();

	for (int i = 0; i < ITERATION_COUNT; ++i)	{
		o[i].foo();
	}

	cout << GetCounter();
	cout << " (OOD, per structure of data iterations, perfect utilization)\n";

	// OOD (Fragmented)
	StartCounter();

	for (int i = 0; i < ITERATION_COUNT; ++i)	{
		f[i].foo();
	}

	cout << GetCounter();
	cout << " (OOD, per structure of data iterations, fragmented utilization)\n";

	delete[] a;
	delete[] b;
	delete[] c;
	delete[] o;
	delete[] f;
}