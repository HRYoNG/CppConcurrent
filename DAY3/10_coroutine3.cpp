#include <iostream>
#include <coroutine>

// step 2. �ڷ�ƾ�� ���Ѿ� �ϴ� ��Ģ
// 1."promise_type"�̶�� ��� Ÿ���� ���� Ÿ���� ��ȯ Ÿ������ �ؾ� �մϴ�.

// 2. promise_type �� Ŭ������ ������ �մϴ�.

class Generator	// �� Ŭ���� �̸��� ����� ������� �ص� �˴ϴ�.
{
public:
	using promise_type = int;
};

Generator foo()
{
	std::cout << "foo 1" << std::endl;

	co_await std::suspend_always(); 

	std::cout << "foo 2" << std::endl;
}


int main()
{
	foo();
}
