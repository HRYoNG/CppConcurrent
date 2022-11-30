#include <thread>  
#include <iostream>
#include "chronometry.h"

const int sz = 10000000;

// �ذ�å 2. ���������� ���� �������� ����
//          ���������� �������Ŀ�
//			������ ����� ���������� �ű⼼��..
long long n1 = 0;
long long n2 = 0;


void f1()
{
	int local = n1;

	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}

	n1 = local;
}
void f2()
{
	int local = n2;
	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}
	n2 = local;
}

void test1()
{
	// ������ �Ѱ��� 2�� �Լ� ����
	f1();
	f2();
}

void test2()
{
	// ������ 2���� ������ �Լ��� ����
	std::thread t1(f1);
	std::thread t2(f2);

	t1.join();
	t2.join();
}

int main()
{
	chronometry(test1); // ������ �Ѱ��� 2���Լ� ����
	chronometry(test2); // ������ 2���� f1, f2 ���ÿ� ����
}
