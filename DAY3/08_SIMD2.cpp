#include <iostream>

int main()
{
	// 모든 배열은 반드시 16의 배수에서 시작되어야 한다는 뜻. 
	__declspec(align(16)) int arr1[4] = { 1,2,3,4 };
	__declspec(align(16)) int arr2[4] = { 5,6,7,8 };
	__declspec(align(16)) int arr3[4] = { 0 };

	// SIMD : Single Instruction Multiple Data
	// 아직 C++이 지원 안하는데,, C++23 부터 많은 STL 명령이 SIMD를 지원할 예정입니다.
	// vector 의 덧셈등이 "SIMD"로 구현될 예정
	__asm
	{
		movdqa xmm0, arr1        // movdqa : move aligned double quad word
		movdqa xmm1, arr2
		paddd xmm0, xmm1        // 한번의 add 명령으로 4개의 data 에 덧셈수행
		movdqa arr3, xmm0
	}

	for (auto e : arr3)
		std::cout << e << std::endl;
}