#include <iostream>
#include <functional>

void foo(int& r)
{
	r = 200;
}

template<typename T>
void forward_parameter_to_foo(T arg)
{
	foo(arg);
}

int main()
{
	int n = 10;

	// call by value 로 설계된 함수에 참조로 전달하기

	// 1. reference_wrapper 를 직접 사용

//	std::reference_wrapper<int> r(n);
//	forward_parameter_to_foo(r);

	// 2. std::ref() 를 사용하면 reference_wrapper 객체를 
	//    만드는 것을 간단하게 할수 있습니다.

	forward_parameter_to_foo( std::ref(n) );
			// => std::ref 함수가 결국
			// => std::reference_wrapper 를 만들어서 반환하게 됩니다.

	std::cout << n << std::endl;
}
// 1. 스레드간에 변수를 참조(주소)로 보내는 것은 아주 위험합니다.
// 2. 그래서 대부분의 스레드 관련 표준함수는 "call by value" 로 
//    설계되어 있습니다. ( value mechanism 이 디폴트 정책 )

// 3. 그런데, 반드시 참조로 보낼 필요가 있다면 "std::ref()" 로 묶어서
//    보내면 됩니다.
//    => 단, 이경우는 결국 주소를 보내는 것이므로 절대 안전하지 않습니다.
//       사용자가 주의 해서 사용해야 합니다.






