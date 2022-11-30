#include <iostream>
#include <coroutine>

// step 5.
// Generator �� ��Ȱ
// 1. promise_type �� �˷��ְ�!!
// 2. �ڷ�ƾ�� �ڵ��� ����

class promise;

class Generator
{
public:
	using promise_type = promise;

	std::coroutine_handle<promise_type> coro; // �ڷ�ƾ �ڵ�

	Generator(std::coroutine_handle<promise_type> c) : coro(c) {}
};

class promise
{
public:
	std::suspend_always initial_suspend() { return {}; }
	std::suspend_always final_suspend() noexcept { return {}; }

	Generator get_return_object() 
	{
		// ���� promise ��ü�� �����ϴ� �ڷ�ƾ �ڵ���
		auto h = std::coroutine_handle<promise>::from_promise(*this);

		return Generator( h );
	};
	
	void unhandled_exception() {}
	void return_void() {}
};


Generator foo()
{

	std::cout << "foo 1" << std::endl;

	co_await std::suspend_always();

	std::cout << "foo 2" << std::endl;
}

int main()
{
	Generator g = foo();
	std::cout << "continue main 1" << std::endl;

	g.coro.resume(); // �ٽ� foo() ȣ��

	std::cout << "continue main 2" << std::endl;

	g.coro.resume();

	std::cout << "continue main 3" << std::endl;
}
