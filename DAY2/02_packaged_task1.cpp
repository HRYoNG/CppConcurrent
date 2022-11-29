#include <iostream>
#include <thread>
#include <future>

// 39 page

// add �Լ��� promise �� ���ؼ� ��ȯ�� ����
// �ٸ� �����忡 ��ȯ
// => ��, add �Լ��� ���鶧 �����带 ��� �ؼ� �����ߴٴ� �ǹ�!!!
// => �����带 ������� �ʾҴٸ� "return ��" ���� ����� ��ȯ!
void add(std::promise<int>& p, int a, int b)
{
	p.set_value(a + b);
}

int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();

	std::thread t(add, std::ref(pm), 10, 20);

	int ret = ft.get();

	t.join();
}



