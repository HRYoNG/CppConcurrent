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

	// call by value �� ����� �Լ��� ������ �����ϱ�

	// 1. reference_wrapper �� ���� ���

//	std::reference_wrapper<int> r(n);
//	forward_parameter_to_foo(r);

	// 2. std::ref() �� ����ϸ� reference_wrapper ��ü�� 
	//    ����� ���� �����ϰ� �Ҽ� �ֽ��ϴ�.

	forward_parameter_to_foo( std::ref(n) );
			// => std::ref �Լ��� �ᱹ
			// => std::reference_wrapper �� ���� ��ȯ�ϰ� �˴ϴ�.


	std::cout << n << std::endl;
}

