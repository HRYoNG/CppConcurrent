#include <iostream>
#include <thread>

// join_thread 

void foo(int a, int b)
{
	std::cout << "foo : " << a << ", " << b << std::endl;
}
//===========================================
// 소멸자에서 자동으로 join 하는 스레드
class scoped_thread
{
	std::thread impl;
public:
	scoped_thread(std::thread&& t) : impl(std::move(t)) {}

	~scoped_thread()
	{
		if (impl.joinable())
			impl.join();
	}
};

class join_thread
{
	std::thread impl;
public:
	// modern C++의 "완벽한 전달" 기술 사용
	template<typename F, typename ... ARGS>
	join_thread(F&& func, ARGS&& ... args)
		: impl( std::forward<F>(func), std::forward<ARGS>(args)... )
	{}


	~join_thread()
	{
		if (impl.joinable())
			impl.join();
	}
};
int main()
{
	scoped_thread sc1( std::thread(&foo, 10, 20) );

//	std::thread t1(&foo, 10, 20); // 이코드 처럼
	join_thread jt(&foo, 10, 20); // 동일하게 사용하면 좋지 않을까요?
}

