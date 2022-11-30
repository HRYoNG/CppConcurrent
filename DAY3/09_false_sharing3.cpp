#include <thread>  
#include <iostream>
#include "chronometry.h"

const int sz = 10000000;

// 해결책 2. 전역변수에 직접 연산하지 말고
//          지역변수에 연산한후에
//			연산의 결과를 전역변수로 옮기세요..
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
	// 스레드 한개로 2개 함수 실행
	f1();
	f2();
}

void test2()
{
	// 스레드 2개로 각각의 함수를 실행
	std::thread t1(f1);
	std::thread t2(f2);

	t1.join();
	t2.join();
}

int main()
{
	chronometry(test1); // 스레드 한개로 2개함수 실행
	chronometry(test2); // 스레드 2개로 f1, f2 동시에 실행
}
