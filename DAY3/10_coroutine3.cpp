#include <iostream>
#include <coroutine>

// step 2. 코루틴이 지켜야 하는 규칙
// 1."promise_type"이라는 멤버 타입을 가진 타입을 반환 타입으로 해야 합니다.

// 2. promise_type 은 클래스로 만들어야 합니다.

class Generator	// 이 클래스 이름은 사용자 마음대로 해도 됩니다.
{
public:
	using promise_type = int;
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
