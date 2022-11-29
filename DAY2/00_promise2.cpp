#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// �Ϲ��Լ� : �Լ� ��ȯ������ ����� ��ȯ
int add1(int a, int b)
{
	int s = a + b;
	return s;
}

// out parameter �� ���� ��ȯ�ϴ� ���.
void add2(int a, int b, int& s)
{
	s = a + b;
}

//==============================================
void add3(int a, int b, std::promise<int>& pr)
{
	int s = a + b;
	std::this_thread::sleep_for(3s); // ����ð��� 3�� �ɸ��ٰ� ����

	// ������ �Ϸ�Ǹ� promise ��ü�� set_value�� �����մϴ�.
	pr.set_value(s); 

	std::this_thread::sleep_for(3s); // ������ �۾��� 3�� ���� �ҿ�!!
}


int main()
{
	// 1. promise ��ü ����.
	std::promise<int> pr;

	// 2. promise �ȿ� �ִ� future ��ü�� �����ϴ�.
	std::future<int> ft = pr.get_future();

	// 3. ������ ������ promise ��ü�� ������ �����ϼ���
	// => std::ref() �Ǵ� std::move() �� ����
	std::thread t(add3, 10, 20, std::ref(pr));

	// �ٸ� �۾��� �ϴٰ�
	std::cout << "main �Լ� ��� ����" << std::endl;

	// 4. �������� ����� �ʿ��ϸ� future��ü���� ��������
	int ret = ft.get(); // �̼���
						// 1. ����� ��� ������ �ٷ� ������
						// 2. ����� ���� ������ ����ϰ� �˴ϴ�.
					 	//    �����尡 "pr.set_value()" �Ҷ� ���� ���
	// ��� ���!!
	std::cout << "������ ���� ��� : " << ret <<  std::endl;


	t.join();
}



