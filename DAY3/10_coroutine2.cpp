#include <iostream>
#include <coroutine>

// step 1. 
// �Լ��� �ڷ�ƾ���� �������!
// => �Լ� �ȿ��� co_await, co_yield, co_return �߿� �Ѱ�����
//		   ����ϸ� �ڷ�ƾ �Դϴ�.

// �Ʒ� �ڵ�� ���� �Դϴ�. 
// => ������ ���� ����

void foo()
{
	std::cout << "foo 1" << std::endl;

	co_await std::suspend_always(); // suspend_always Ÿ���� �ӽð�ü����

	std::cout << "foo 2" << std::endl;
}

int main()
{
	foo();
}
