#include <iostream>

int main()
{
	int v1 = 10, v2 = 20;

	// C++ ���� : �̵� �Ұ����� ����, �ǹ̷������� ��� �Դϴ�.
	//			  "r1 = r2" �� ����Ű�� ������ ���� �����մϴ�.
	// int& r1 = v1;
	// int& r2 = v2;

	// �̵� ������ ���� : ���� ����� ������ �̵��մϴ�.(C++11)
	std::reference_wrapper<int> r1(v1);
	std::reference_wrapper<int> r2(v2);

	r1 = r2;

	// �Ʒ� �ڵ� ��� ������ ������		// C++����
	std::cout << v1 << std::endl;	// 20
	std::cout << v2 << std::endl;	// 20
	std::cout << r1 << std::endl;	// 20
	std::cout << r2 << std::endl;	// 20
}