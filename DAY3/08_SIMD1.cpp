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
			// => 위 기계어 코드가 배열의 크기(4) 만큼 반복실행
	}
	// MIMD : Mutilple Instruction Multiple Data
	// => N개의 데이타에 연산을 하려면 N번의 명령 필요




	for (auto e : arr3)
		std::cout << e << std::endl;
}