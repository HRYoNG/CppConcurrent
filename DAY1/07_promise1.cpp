#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

int add1(int a, int b)
{
	int s = a + b;
	return s;
}


int main()
{
	std::thread t(add, 10, 20);

	t.join();
}



