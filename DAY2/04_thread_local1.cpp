#include <iostream>
#include <thread>
#include <string_view>

// 73 page

// 3의 배수를 차례대로 반환 하는 함수를 생각해 봅시다.(3, 6, 9)
int next3times()
{
//	int n = 0;			// 지역변수, stack 사용, 함수 호출이 종료되면 파괴!

//	static int n = 0;	// static 지역변수, static(data) 메모리사용, 
						// 함수 호출이 종료되어도 파괴 안됨.

	thread_local int n = 0; // thread 별로 따로 사용하는 staitic메모리공간
						    // 함수 호출이 종료되어도 파괴 되지 않은 변수
							// thread_local 은 키워드 입니다.
							// "std::" 필요 없습니다.
							// TLS : Thread Local Storage 또는
							// TSS : Thread Specific Storage 라고 합니다.
	n = n + 3;
	return n;
}

void foo(const std::string& name)
{
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
}

int main()
{
//	foo("A");
	// 2개의 스레드가 foo 실행
	std::thread t1(&foo, "A");
	std::thread t2(&foo, "\tB");

	t1.join();
	t2.join();
}

// stack  : 스레드당 한개,    함수 호출 종료시 파괴 
// static : 모든 스레드 공유, 함수 호출 종료시 파괴 안됨
// 전역변수도 thread_local 됩니다.
int g1 = 0;				// 모든 스레드가 공유
thread_local int g2 = 0;// 스레드당 한개의 전역변수


