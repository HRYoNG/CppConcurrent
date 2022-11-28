
// 4���ҽ��� 3���� ���� �ϼ���
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

	forward_parameter_to_foo(n);

	std::cout << n << std::endl;
}

