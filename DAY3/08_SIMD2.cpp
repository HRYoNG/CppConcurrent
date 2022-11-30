#include <iostream>

int main()
{
	// ��� �迭�� �ݵ�� 16�� ������� ���۵Ǿ�� �Ѵٴ� ��. 
	__declspec(align(16)) int arr1[4] = { 1,2,3,4 };
	__declspec(align(16)) int arr2[4] = { 5,6,7,8 };
	__declspec(align(16)) int arr3[4] = { 0 };

	// SIMD : Single Instruction Multiple Data
	// ���� C++�� ���� ���ϴµ�,, C++23 ���� ���� STL ����� SIMD�� ������ �����Դϴ�.
	// vector �� �������� "SIMD"�� ������ ����
	__asm
	{
		movdqa xmm0, arr1        // movdqa : move aligned double quad word
		movdqa xmm1, arr2
		paddd xmm0, xmm1        // �ѹ��� add ������� 4���� data �� ��������
		movdqa arr3, xmm0
	}

	for (auto e : arr3)
		std::cout << e << std::endl;
}