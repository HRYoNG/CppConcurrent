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
	scoped_thread( std::thread&& t ) : impl( std::move(t) ) {}

	~scoped_thread()
	{
		if (impl.joinable())
			impl.join();
	}
};



int main()
{
	// std::thread 사용시 항상, join() 또는 detach()가 필요 합니다.
    std::thread t1(&foo, 10, 20);
	t1.join();

	// scoped_thread 사용하기
	std::thread t2(&foo, 10, 20);

//	scoped_thread sc1(t2);	// error. rvalue 만 받을수 있습니다.
	scoped_thread sc1(std::move(t2)); // ok

	// 아래 처럼 사용하면 sc2가 파괴 될때 자동으로 join 됩니다.
	scoped_thread sc2( std::thread(&foo, 10, 20) );
}

