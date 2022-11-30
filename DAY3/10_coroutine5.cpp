#include <iostream>
#include <coroutine>

// step 4. promise_type �� Ŭ������ 5�� ��� �Լ�

class promise;

class Generator
{
public:
	using promise_type = promise;
};

class promise	
{				
public:
	std::suspend_always initial_suspend() { return {}; }
	std::suspend_always final_suspend() noexcept { return {}; }
	Generator get_return_object() { return Generator(); };
	void unhandled_exception() {}
	void return_void() {}
};
Generator foo()
{
	//==========================================================
	// �����Ϸ��� "�ڷ�ƾ�� ���� �ڵ带 �߰�" �մϴ�

	// 1. "sizeof(�����������)+ sizeof(promise_type) + ��Ÿ����"�� ����
	//	  �޸𸮸� ���� �Ҵ�.

	// 2. promise_type �ȿ� �ִ� ��ӵ� �Լ��� get_return_object() �� ȣ���ؼ�
	//	  Generator Ÿ���� ��ü ����

	// 3. promise_type �ȿ� �ִ� initial_update() ȣ��

	// 4. 3���� ���� ��ü�� return!!.  ��, ���⼭ �ٷ� main ���� ����

	//=========================================================
	std::cout << "foo 1" << std::endl;

	co_await std::suspend_always();

	std::cout << "foo 2" << std::endl;
}


int main()
{
	foo();
}
