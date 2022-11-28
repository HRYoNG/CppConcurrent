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

