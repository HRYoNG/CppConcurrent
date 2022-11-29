#include <iostream>
#include <thread>
#include <string_view>

// 73 page

// 3�� ����� ���ʴ�� ��ȯ �ϴ� �Լ��� ������ ���ô�.(3, 6, 9)
int next3times()
{
//	int n = 0;			// ��������, stack ���, �Լ� ȣ���� ����Ǹ� �ı�!

	static int n = 0;	// static ��������, static(data) �޸𸮻��, 
						// �Լ� ȣ���� ����Ǿ �ı� �ȵ�.
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
	foo("A");
}



