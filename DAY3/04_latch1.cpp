#include <iostream>
#include <mutex>
#include <thread>
#include <latch> // C++20

// C++20 에서 추가된 동기화 도구 : semaphore, latch, barrier 

// latch : 카운트 기반의 가벼운 동기화 도구 입니다.
// 
// => 없어도 condition_variable 등으로 모두 구현 가능한데...
// => 직접 구현할 필요 없이 간단하게 사용하기 위한 도구.


std::latch complete_cnt(3); // 내부적으로 "3"을 보관
							// wait() 멤버 함수로 0을 될때를 대기 가능

void foo(std::string name)
{
	std::cout << "start  work : " << name << std::endl;
	
	std::this_thread::sleep_for(1s);

	std::cout << "finish work : " << name << std::endl;
	complete_cnt.count_down(); // --count

	std::cout << "go home     : " << name << std::endl;
}

int main()
{
	std::jthread t1(foo, "kim"), t2(foo, "lee"), t3(foo, "park");

	complete_cnt.wait(); // count 가 0이 될때 까지 대기 합니다.

	std::cout << "receive signal" << std::endl;
}
