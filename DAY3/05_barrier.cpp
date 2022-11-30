#include <iostream>
#include <mutex>
#include <thread>
#include <latch>   // C++20
#include <barrier> // C++20
#include <chrono>
using namespace std::literals;


//std::latch complete_cnt(3); // 1ȸ�� ��밡�� �մϴ�.

// ���� : barrier �� ���޵Ǵ� �Լ��� �ݵ�� "noexcept" �� ������ �մϴ�.
void oncomplete() noexcept
{
	std::cout << "=============== oncomplete ==============\n";
}


//std::barrier complete_cnt(3, oncomplete); // ������ ��밡���� latch �Դϴ�.
									// ī��Ʈ�� 0�� �Ǹ�
									// "2��°���ڷ� ������ �Լ�"�� ȣ��.

std::barrier complete_cnt(3,
	[]()noexcept {
		std::cout << "=============== oncomplete ==============\n"; });


void foo(std::string name)
{
	std::cout << "start  work : " << name << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "finish work : " << name << std::endl;

	complete_cnt.arrive_and_wait(); // wait �� �����
									// �ٽ� count reset�˴ϴ�. 3 ����

	std::cout << "have dinner : " << name << std::endl;

	complete_cnt.arrive_and_wait();

	std::cout << "go home     : " << name << std::endl;
}





int main()
{
	std::jthread t1(foo, "kim"), t2(foo, "lee"), t3(foo, "park");


	std::cout << "receive signal" << std::endl;
}
