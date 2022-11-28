#include <iostream>

// reference_wrapper �� ���� ����� ���ô�.
template<typename T>
struct reference_wrapper
{
	T* pobj;
	reference_wrapper(T& obj) : pobj(&obj) {}

	// "raw reference" �� ��ȯ�� ����Ѵ�.
	operator T& const { return *pobj; }
};

int main()
{
	int v1 = 10, v2 = 20;

	reference_wrapper<int> r1(v1);
	reference_wrapper<int> r2(v2);

	r1 = r2;

	int& r3 = r1;	// r1.operator int&() ��� �Լ� ȣ��

	std::cout << v1 << std::endl;	// 20		10
	std::cout << v2 << std::endl;	// 20		20
	std::cout << r1 << std::endl;	// 20		20
	std::cout << r2 << std::endl;	// 20		20
}