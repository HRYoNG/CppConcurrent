#include <iostream>

int main()
{
	int v1 = 10, v2 = 20;

	// C++ 참조 : 이동 불가능한 참조, 의미론적으로 상수 입니다.
	//			  "r1 = r2" 는 가리키던 변수의 값을 대입합니다.
	// int& r1 = v1;
	// int& r2 = v2;

	// 이동 가능한 참조 : 대입 연산시 참조가 이동합니다.(C++11)
	std::reference_wrapper<int> r1(v1);
	std::reference_wrapper<int> r2(v2);

	r1 = r2;

	// reference_wrapper 은 "raw reference"로 암시적 변환도 됩니다.
	int& r3 = r1;

	// 아래 코드 결과 예측해 보세요		// C++참조	reference_wrapper
	std::cout << v1 << std::endl;	// 20		10
	std::cout << v2 << std::endl;	// 20		20
	std::cout << r1 << std::endl;	// 20		20
	std::cout << r2 << std::endl;	// 20		20
}