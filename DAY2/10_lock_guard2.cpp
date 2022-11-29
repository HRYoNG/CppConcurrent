#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

void foo()
{
	// lock_guard �� ����ϸ� ���ؽ��� unlock �� ���� �Ҹ��ڿ����� ����˴ϴ�.
	// => �Լ� ���� ������ �ƴ� ������ unlock �� �ʿ��ϸ� {}�� ����ϼ���
	{
		std::lock_guard<std::mutex> lg(m);
		std::cout << "using shared data" << std::endl;
	}

	std::cout << "�� �κ��� ����ȭ �ȵ�" << std::endl;
}


int main()
{
	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}



