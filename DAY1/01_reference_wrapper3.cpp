
// 4���ҽ��� 3���� ���� �ϼ���
#include <iostream>
#include <functional>

void foo(int& r)
{
	r = 200;
}

// ���޹��� ���ڸ� foo ���� �����ϴ� �Լ� ���ø�
template<typename T>
void forward_parameter_to_foo(T arg)
{
	foo(arg);
}

int main()
{
	int n = 10;

//	forward_parameter_to_foo(n);

	// ���� �ƴ� �޸𸮿� ���� ����(�ּ�)�� �����մϴ�.
//	forward_parameter_to_foo(&n);
				// => ���纻�� �ƴ� �޸� ����(�ּ�)�� ����
				// => ������ �ּҰ� �ٽ� int& �� ���޵ɼ� �����Ƿ�
				// => "foo(arg)" ���� ����!! arg = int* �̹Ƿ�

	// �ᱹ �ʿ��� ����
	// 1. ���������δ� �޸� �ּҸ� �����ϴµ�
	// 2. ������ ��ȯ�� �����ؾ� �մϴ�.
	std::reference_wrapper<int> r(n);

	forward_parameter_to_foo(r);
		

	std::cout << n << std::endl;
}

