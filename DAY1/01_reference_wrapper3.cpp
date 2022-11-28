
// 4번소스를 3번에 복사 하세요
#include <iostream>
#include <functional>

void foo(int& r)
{
	r = 200;
}

// 전달받은 인자를 foo 에게 전달하는 함수 템플릿
template<typename T>
void forward_parameter_to_foo(T arg)
{
	foo(arg);
}

int main()
{
	int n = 10;

//	forward_parameter_to_foo(n);

	// 값이 아닌 메모리에 대한 정보(주소)를 전달합니다.
//	forward_parameter_to_foo(&n);
				// => 복사본이 아닌 메모리 정보(주소)를 전달
				// => 하지만 주소가 다시 int& 로 전달될수 없으므로
				// => "foo(arg)" 에서 에러!! arg = int* 이므로

	// 결국 필요한 것은
	// 1. 내부적으로는 메모리 주소를 보관하는데
	// 2. 참조로 변환이 가능해야 합니다.
	std::reference_wrapper<int> r(n);

	forward_parameter_to_foo(r);
		

	std::cout << n << std::endl;
}

