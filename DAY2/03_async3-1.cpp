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
	// 핵심 : async 의 반환값(future)를 받지 않을때 나타나는 현상
	std::async(add, 10, 20);

	std::cout << "main 계속 실행" << std::endl;
}	

