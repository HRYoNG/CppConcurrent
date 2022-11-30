#include <iostream>
#include <coroutine>

// step 8. Generator �� () ������ �ڵ� �� ������ ������


class Generator
{
public:

	class promise
	{
		int value;
	public:

		int get_value() const { return value; }

		std::suspend_always yield_value(int n)
		{
			value = n;
			return {};
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



	using promise_type = promise;

	std::coroutine_handle<promise_type> coro; // �ڷ�ƾ �ڵ�

	Generator(std::coroutine_handle<promise_type> c) : coro(c) {}

	~Generator() { if (coro) coro.destroy(); }

	int operator()() const 
	{
		coro.resume();	// �簳�ϰ�!!

		int ret = coro.promise().get_value(); // co_yield 10 ����
											// ������ ���� ������
		return ret;
	}
};





Generator foo()
{
	std::cout << "foo 1" << std::endl;

	co_yield 10; 

	std::cout << "foo 2" << std::endl;

	co_yield 20;
}



int main()
{
	Generator g = foo();

	std::cout << "continue main 1" << std::endl;
	
	int ret = g();

	std::cout << "continue main 2 : " << ret << std::endl;

	ret = g();

	std::cout << "continue main 3 : " << ret << std::endl;
}
