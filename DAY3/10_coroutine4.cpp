#include <iostream>
#include <coroutine>

// step 3. promise_type �� Ŭ������ ����

// ���� ���� : 

class promise;

class Generator	
{
public:
	using promise_type = promise;
};

class promise	// �ƹ� �̸��� ����ص� �˴ϴ�. 
{				// �� Generator ������ "promise_type" ���� �����ϸ�˴ϴ�.
public:
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
