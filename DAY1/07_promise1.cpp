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

// 스레드가 수행한 함수의 반환값을 꺼내려면
// => out parameter 로 해야 합니다.
void add2(int a, int b, int& s)
{
	s = a + b;
}

int main()
{
	// 핵심 1. 스레드가 아닌 직접 호출은 함수의 결과를 반환값으로 받으면 됩니다.
	int ret1 = add1(10, 20);

	// 핵심 2. 스레드의 수행 결과를 직접 꺼내려면 out parameter 전달
	int ret2 = 0;

	std::thread t(add2, 10, 20, std::ref(ret2) );

	t.join();

	std::cout << ret2 << std::endl;
}



