#include <iostream>
#include <coroutine>

// step 4. promise_type 을 클래스의 5개 멤버 함수

class promise;

class Generator
{
public:
	using promise_type = promise;
};

class promise	
{				
public:
	std::suspend_always initial_suspend() { return {}; }
	std::suspend_always final_suspend() noexcept { return {}; }
	Generator get_return_object() { return Generator(); };
	void unhandled_exception() {}
	void return_void() {}
};
Generator foo()
{
	//==========================================================
	// 컴파일러가 "코루틴을 위한 코드를 추가" 합니다

	// 1. "sizeof(모든지역변수)+ sizeof(promise_type) + 기타정보"를 담을
	//	  메모리를 힙에 할당.

	// 2. promise_type 안에 있는 약속된 함수인 get_return_object() 를 호출해서
	//	  Generator 타입의 객체 생성

	// 3. promise_type 안에 있는 initial_update() 호출

	// 4. 3에서 만든 객체를 return!!.  즉, 여기서 바로 main 으로 복귀

	//=========================================================
	std::cout << "foo 1" << std::endl;

	co_await std::suspend_always();

	std::cout << "foo 2" << std::endl;
}


int main()
{
	foo();
}
