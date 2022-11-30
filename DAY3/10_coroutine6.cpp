#include <iostream>
#include <coroutine>

// step 5.
// Generator 의 역활
// 1. promise_type 을 알려주고!!
// 2. 코루틴의 핸들을 보관

class promise;

class Generator
{
public:
	using promise_type = promise;

	std::coroutine_handle<promise_type> coro; // 코루틴 핸들

	Generator(std::coroutine_handle<promise_type> c) : coro(c) {}
};

class promise
{
public:
	std::suspend_always initial_suspend() { return {}; }
	std::suspend_always final_suspend() noexcept { return {}; }

	Generator get_return_object() 
	{
		// 현재 promise 객체가 관리하는 코루틴 핸들얻기
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

	g.coro.resume(); // 다시 foo() 호출

	std::cout << "continue main 2" << std::endl;

	g.coro.resume();

	std::cout << "continue main 3" << std::endl;
}
