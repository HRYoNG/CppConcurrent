#include <iostream>
#include <coroutine>

// step 7. promise �� ��Ȱ!

// Generator : coroutine �� �ڵ��� �����ϰ�, promise�� Ÿ�� �̸��� ����


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
	int value;
public:
	// �Ʒ� �Լ��� ��ӵ� �Լ� �ƴմϴ�. 
	int get_value() const { return value; }

	// �Ʒ� �Լ� ���� ��� ��ӵǾ� �ִ� �Լ� �Դϴ�.
	std::suspend_always yield_value(int n)
	{
		value = n;
		return {}; // suspend_always{} �� ����
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

	co_yield 10; // ���߰� ȣ���ڿ� 10 ����	
				 // co_await  promise��ü.yield_value(10);
				// 1. promise �ȿ� yield_value() �� �־�� �Ѵ�.
				// 2. ��ȯ Ÿ���� suspend_always() �Ǵ� never �Ǵ� ����ڰ�
				//		���� Ÿ��.


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
