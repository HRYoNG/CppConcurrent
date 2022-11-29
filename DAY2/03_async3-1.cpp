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
	// => ��ġ, ������ ������ �ƴ�, �Ϲ� ȣ�� ó�� �����մϴ�.
	// => add �Լ��� ����Ǿ�� "main �� ��� ����" �˴ϴ�.
	// ���� : async �� ��ȯ�ϴ� ���� �ӽð�ü�ε�, 
	//       �ӽð�ü�� �ش� ������ ������ �ı� �˴ϴ�.
	//       �̶� �ӽð�ü�� future �� �Ҹ��ڿ��� ���(getȣ��)�ϰԵ˴ϴ�.
	std::async(add, 10, 20);

	std::cout << "main ��� ����" << std::endl;
}	
/*
// async �� future �� �� Ÿ������ ��ȯ �մϴ�.
// �ӽð�ü�� ��ȯ �˴ϴ�.
std::future<int> async(...)
{
	std::future<int> ret = ....;
	return ret;
}
*/
