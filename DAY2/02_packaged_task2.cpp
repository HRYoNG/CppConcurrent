#include <iostream>
#include <thread>
#include <future>

// �����带 ������� �ʰ� ������� �Ϲ� �Լ��� ��κ�
// "return ��" ���� ����� �����մϴ�.
int add(int a, int b)
{
	std::cout << "add" << std::endl;

	return a + b;
}

int main()
{
	// packaged_task : "return ��" ���� ����� ��ȯ�ϴ� �Լ���
	//				   ������� �����ϰ� ����� ��� ����.

	// 1. packaged_task �� ��ü�� ����� future ��ü�� ��������
	std::packaged_task<int(int, int)> task(add);

	std::future<int> ft = task.get_future();

	// 2. packaged_task �� Ÿ���� ��ü�� "task" �� ()�����ڰ� ������
	// �Ǿ� �ֽ��ϴ�.
	// task(10, 20); // add(10,20) �� ����˴ϴ�.
				  // ��, ���ڵ�� ������� �����ϴ� ���� �ƴմϴ�.
				  // ����, ����� future�� ���ؼ� ������ �մϴ�.

	// 3. task �� ������� �����ϸ� �˴ϴ�.
	// => task ���޽� "std::ref()" �Ǵ� "std::move()" �����մϴ�.
	// std::ref(task)  : task ��ü�� ��� ����ϰ� ������
	// std::move(task) : task ��ü�� �� �̻� ����Ҽ� �����ϴ�.
	//					=> �ѹ��� ����Ѵٸ� move �� �ϼ���
	std::thread t(std::move(task), 10, 20);

	int ret = ft.get();

	std::cout << ret << std::endl;

	t.join();

	// ����
//	std::thread t1(add, 10, 20); // add�� ����� ���� ����� �����ϴ�
								 // promise ����ؾ� �մϴ�.
								 // => add �Լ� ��� �����ؾ� �մϴ�.

//	std::thread t2(std::ref(task), 10, 20);
								// add �Լ��� ����� �������� �ʰ�
								// ����� ��ȯ ������ �ֽ��ϴ�.
								// future ���
}

