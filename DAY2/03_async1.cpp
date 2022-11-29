// async1 - packaged task2 ����
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

//------------------------------------------------
// async          : �Լ��� �񵿱�� ����
//				    ����� future �� ��ȯ
//					���������� packaged_task �� ����
//----------------------------------------------
// packaged_task  : "return ��"���� �� �Լ��� ������� �����ϱ� ����
//					���������� promise future ���
//---------------------------------------------
// promise/future : ������ ����� ������� ����
//----------------------------------------------
// std::thread : ���� �⺻ Ŭ����
//-----------------------------------------------
// OS �ý��� �� : CreateThread(), pthread_create()


// std::thread vs std::async

// std::thread : �����带 ����� ���� �⺻ ���� ����
//				 C++������ ���� ���� ������ ����
//			     ������� ������ �Լ��� ����� ������ ����.





int add(int a, int b)
{
	std::cout << "add" << std::endl;

	std::this_thread::sleep_for(2s);
	return a + b;
}

int main()
{
	// std::async : Ư�� �Լ��� �񵿱�(������)�� �����ϰ�
	//				����� ������ �ִ� future�� ��ȯ
	std::future<int> ft = std::async(add, 10, 20);
			
	std::cout << "main ��� ����" << std::endl;

	int ret = ft.get();

	std::cout << ret << std::endl;
}

