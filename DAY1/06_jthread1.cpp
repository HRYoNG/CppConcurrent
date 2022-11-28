#include <iostream>
#include <thread>

// join_thread 

void foo(int a, int b)
{
	std::cout << "foo : " << a << ", " << b << std::endl;
}
//===========================================
// �Ҹ��ڿ��� �ڵ����� join �ϴ� ������
class scoped_thread
{
	std::thread impl;
public:
	scoped_thread( std::thread&& t ) : impl( std::move(t) ) {}

	~scoped_thread()
	{
		if (impl.joinable())
			impl.join();
	}
};



int main()
{
	// std::thread ���� �׻�, join() �Ǵ� detach()�� �ʿ� �մϴ�.
    std::thread t1(&foo, 10, 20);
	t1.join();

	// scoped_thread ����ϱ�
	std::thread t2(&foo, 10, 20);

//	scoped_thread sc1(t2);	// error. rvalue �� ������ �ֽ��ϴ�.
	scoped_thread sc1(std::move(t2)); // ok

	// �Ʒ� ó�� ����ϸ� sc2�� �ı� �ɶ� �ڵ����� join �˴ϴ�.
	scoped_thread sc2( std::thread(&foo, 10, 20) );
}

