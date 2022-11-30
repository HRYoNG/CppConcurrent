#include <iostream>
#include <mutex>
#include <thread>
#include <latch>   // C++20
#include <barrier> // C++20
#include <chrono>
using namespace std::literals;


//std::latch complete_cnt(3); // 1회만 사용가능 합니다.

// 주의 : barrier 에 전달되는 함수는 반드시 "noexcept" 로 만들어야 합니다.
void oncomplete() noexcept
{
	std::cout << "=============== oncomplete ==============\n";
}


//std::barrier complete_cnt(3, oncomplete); // 여러번 사용가능한 latch 입니다.
									// 카운트가 0이 되면
									// "2번째인자로 전달한 함수"가 호출.

std::barrier complete_cnt(3,
	[]()noexcept {
		std::cout << "=============== oncomplete ==============\n"; });


void foo(std::string name)
{
	std::cout << "start  work : " << name << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "finish work : " << name << std::endl;

	complete_cnt.arrive_and_wait(); // wait 를 통과시
									// 다시 count reset됩니다. 3 으로

	std::cout << "have dinner : " << name << std::endl;

	complete_cnt.arrive_and_wait();

	std::cout << "go home     : " << name << std::endl;
}





int main()
{
	std::jthread t1(foo, "kim"), t2(foo, "lee"), t3(foo, "park");


	std::cout << "receive signal" << std::endl;
}
