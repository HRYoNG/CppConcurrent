#include <iostream>
#include <coroutine>

// step 3. promise_type 을 클래스로 설계

// 아직 에러 : 

class promise;

class Generator	
{
public:
	using promise_type = promise;
};

class promise	// 아무 이름을 사용해도 됩니다. 
{				// 위 Generator 에서만 "promise_type" 으로 노출하면됩니다.
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
