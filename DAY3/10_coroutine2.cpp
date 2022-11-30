#include <iostream>
#include <coroutine>

// step 1. 
// 함수를 코루틴으로 만들려면!
// => 함수 안에서 co_await, co_yield, co_return 중에 한가지라도
//		   사용하면 코루틴 입니다.

// 아래 코드는 에러 입니다. 
// => 이유는 다음 예제

void foo()
{
	std::cout << "foo 1" << std::endl;

	co_await std::suspend_always(); // suspend_always 타입의 임시객체생성

	std::cout << "foo 2" << std::endl;
}

int main()
{
	foo();
}
