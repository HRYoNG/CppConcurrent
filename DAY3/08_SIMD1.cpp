#include <iostream>

int main()
{
	int arr1[4] = { 1,2,3,4 };
	int arr2[4] = { 5,6,7,8 };
	int arr3[4] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		arr3[i] = arr1[i] + arr2[i];

			// mov eax, arr1[i]
			// add eax, arr2[i]
			// mov arr3[i], eax
			// => �� ���� �ڵ尡 �迭�� ũ��(4) ��ŭ �ݺ�����
	}
	// MIMD : Mutilple Instruction Multiple Data
	// => N���� ����Ÿ�� ������ �Ϸ��� N���� ��� �ʿ�




	for (auto e : arr3)
		std::cout << e << std::endl;
}