// async1 - packaged task2 복사
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

int add(int a, int b)
{
	std::cout << "add" << std::endl;

	std::this_thread::sleep_for(2s);
	return a + b;
}

int main()
{
	// std::async : 특정 함수를 비동기(스레드)로 실행하고
	//				결과를 얻을수 있는 future를 반환
	std::future<int> ft = std::async(add, 10, 20);
			
	std::cout << "main 계속 실행" << std::endl;

	int ret = ft.get();

	std::cout << ret << std::endl;
}

