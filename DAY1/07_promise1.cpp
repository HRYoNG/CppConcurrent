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
// => out parameter (또는 전역변수)로 해야 합니다.
// => 그런데, 이 방식은 연산의 종료를 대기할수 없습니다.
//    스레드의 종료를 대기하게 됩니다.
// => 해결책 : 1. promise & future
//            2. packaged_task
//			  3. async
// => 결과뿐 아니라 "예외의 전달" 도 가능합니다.
void add2(int a, int b, int& s)
{
	s = a + b;

	// 연산은 종료 되었지만, 
	// 마무리 작업을 해야 한다고 생각해 보세요.
	std::this_thread::sleep_for(3s);
}

int main()
{
	// 핵심 1. 스레드가 아닌 직접 호출은 함수의 결과를 반환값으로 받으면 됩니다.
	int ret1 = add1(10, 20);

	// 핵심 2. 스레드의 수행 결과를 직접 꺼내려면 out parameter 전달
	int ret2 = 0;

	std::thread t(add2, 10, 20, std::ref(ret2) );

	t.join();	// 연산의 종료를 대기하는 것이 아니라!!!
				// 스레드의 종료를 대기하는 것!

	std::cout << ret2 << std::endl;
}



