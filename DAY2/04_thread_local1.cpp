#include <iostream>
#include <thread>
#include <string_view>

// 73 page

// 3�� ����� ���ʴ�� ��ȯ �ϴ� �Լ��� ������ ���ô�.(3, 6, 9)
int next3times()
{
//	int n = 0;			// ��������, stack ���, �Լ� ȣ���� ����Ǹ� �ı�!

//	static int n = 0;	// static ��������, static(data) �޸𸮻��, 
						// �Լ� ȣ���� ����Ǿ �ı� �ȵ�.

	thread_local int n = 0; // thread ���� ���� ����ϴ� staitic�޸𸮰���
						    // �Լ� ȣ���� ����Ǿ �ı� ���� ���� ����
							// thread_local �� Ű���� �Դϴ�.
							// "std::" �ʿ� �����ϴ�.
							// TLS : Thread Local Storage �Ǵ�
							// TSS : Thread Specific Storage ��� �մϴ�.
	n = n + 3;
	return n;
}

void foo(const std::string& name)
{
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
}

int main()
{
//	foo("A");
	// 2���� �����尡 foo ����
	std::thread t1(&foo, "A");
	std::thread t2(&foo, "\tB");

	t1.join();
	t2.join();
}

// stack  : ������� �Ѱ�,    �Լ� ȣ�� ����� �ı� 
// static : ��� ������ ����, �Լ� ȣ�� ����� �ı� �ȵ�
// ���������� thread_local �˴ϴ�.
int g1 = 0;				// ��� �����尡 ����
thread_local int g2 = 0;// ������� �Ѱ��� ��������


