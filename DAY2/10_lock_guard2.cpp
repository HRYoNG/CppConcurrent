#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

void foo()
{
	// lock_guard 를 사용하면 뮤텍스의 unlock 은 오직 소멸자에서만 수행됩니다.
	// => 함수 종료 시점이 아닌 곳에서 unlock 이 필요하면 {}을 사용하세요
	{
		std::lock_guard<std::mutex> lg(m);
		std::cout << "using shared data" << std::endl;
	}

	std::cout << "이 부분은 동기화 안됨" << std::endl;
}


int main()
{
	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}



