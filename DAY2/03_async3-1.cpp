// async1 - packaged task2 ����
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
	// �ٽ� : async �� ��ȯ��(future)�� ���� ������ ��Ÿ���� ����
	std::async(add, 10, 20);

	std::cout << "main ��� ����" << std::endl;
}	

