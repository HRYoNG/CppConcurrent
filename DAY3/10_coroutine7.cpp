#include <iostream>
#include <coroutine>

// step 6. suspend_never, suspend_always

class promise;

class Generator
{
public:
	using promise_type = promise;

	std::coroutine_handle<promise_type> coro; // �ڷ�ƾ �ڵ�

	Generator(std::coroutine_handle<promise_type> c) : coro(c) {}

	~Generator() { if (coro) coro.destroy(); }

	void operator()() const { coro.resume(); }
};




class promise
{
public:
	std::suspend_always initial_suspend() { return {}; }
	std::suspend_always final_suspend() noexcept { return {}; }

	Generator get_return_object()
	{
	
		auto h = std::coroutine_handle<promise>::from_promise(*this);

		return Generator(h);
	};

	void unhandled_exception() {}
	void return_void() {}
};


Generator foo()
{
	std::cout << "foo 1" << std::endl;

//	co_await std::suspend_always(); // main ���� ���ư���!
	co_await std::suspend_never();  // ��� ����

		// "co_await ��ü" �Դϴ�. 
		// => ��ü�� �ִ� ��ӵ� ��� �Լ��� ȣ���ؼ� ��������, ��� ���������� ����
		// => ���� �� �ܰ迡�� �߰����� �۾� ����.


	std::cout << "foo 2" << std::endl;
}



int main()
{
	Generator g = foo();
	std::cout << "continue main 1" << std::endl;

	g.coro.resume(); 

	std::cout << "continue main 2" << std::endl;

//	g.coro.resume();
//	std::cout << "continue main 3" << std::endl;
}
