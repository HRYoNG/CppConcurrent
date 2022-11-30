#include <iostream>
#include <coroutine>

// step 7. promise 의 역활!

// Generator : coroutine 의 핸들을 전달하고, promise의 타입 이름을 보관


class promise;

class Generator
{
public:
	using promise_type = promise;

	std::coroutine_handle<promise_type> coro; // 코루틴 핸들

	Generator(std::coroutine_handle<promise_type> c) : coro(c) {}

	~Generator() { if (coro) coro.destroy(); }

	void operator()() const { coro.resume(); }
};




class promise
{
	int value;
public:
	// 아래 함수는 약속된 함수 아닙니다. 
	int get_value() const { return value; }

	// 아래 함수 들은 모두 약속되어 있는 함수 입니다.
	std::suspend_always yield_value(int n)
	{
		value = n;
		return {}; // suspend_always{} 와 동일
	}


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

//	co_await std::suspend_always(); 

	co_yield 10; // 멈추고 호출자에 10 전달	
				 // co_await  promise객체.yield_value(10);
				// 1. promise 안에 yield_value() 가 있어야 한다.
				// 2. 반환 타입은 suspend_always() 또는 never 또는 사용자가
				//		만든 타입.


	std::cout << "foo 2" << std::endl;

	co_yield 20;
}



int main()
{
	Generator g = foo();
	std::cout << "continue main 1" << std::endl;

	g.coro.resume(); 

	int ret = g.coro.promise().get_value();
	std::cout << "continue main 2 : " << ret << std::endl;

	g.coro.resume();
	ret = g.coro.promise().get_value();

	std::cout << "continue main 3 : " << ret << std::endl;
}
