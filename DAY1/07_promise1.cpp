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

// �����尡 ������ �Լ��� ��ȯ���� ��������
// => out parameter �� �ؾ� �մϴ�.
void add2(int a, int b, int& s)
{
	s = a + b;
}

int main()
{
	// �ٽ� 1. �����尡 �ƴ� ���� ȣ���� �Լ��� ����� ��ȯ������ ������ �˴ϴ�.
	int ret1 = add1(10, 20);

	// �ٽ� 2. �������� ���� ����� ���� �������� out parameter ����
	int ret2 = 0;

	std::thread t(add2, 10, 20, std::ref(ret2) );

	t.join();

	std::cout << ret2 << std::endl;
}



