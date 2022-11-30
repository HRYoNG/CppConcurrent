#include <iostream>
#include <mutex>
#include <thread>
#include <latch> // C++20

// C++20 ���� �߰��� ����ȭ ���� : semaphore, latch, barrier 

// latch : ī��Ʈ ����� ������ ����ȭ ���� �Դϴ�.
// 
// => ��� condition_variable ������ ��� ���� �����ѵ�...
// => ���� ������ �ʿ� ���� �����ϰ� ����ϱ� ���� ����.


std::latch complete_cnt(3); // ���������� "3"�� ����
							// wait() ��� �Լ��� 0�� �ɶ��� ��� ����

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

	complete_cnt.wait(); // count �� 0�� �ɶ� ���� ��� �մϴ�.

	std::cout << "receive signal" << std::endl;
}
