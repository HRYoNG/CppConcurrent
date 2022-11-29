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

	std::cout << "finish add" << std::endl;
	return a + b;
}

int main()
{
	std::future<int> ft = std::async(add, 10, 20);

	std::cout << "main 계속 실행" << std::endl;

	// int ret = ft.get();	// 결과를 대기 하지 않으면 어떨께 될까 ?

}	// <= 지역변수 ft 가 파괴 됩니다.
	// <= ft 의 소멸자가 호출됩니다.
	// <= 사용자가 "ft.get()" 을 호출한 적이 없으면 소멸자에서 "ft.get()"
	// <= 즉, async 로 수행한 함수의 종료를 대기하게 됩니다.

