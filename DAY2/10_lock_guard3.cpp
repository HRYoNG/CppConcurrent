#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m1;
std::mutex m2;

void foo()
{
	std::lock_guard<std::mutex> g1(m1); 
			// => lock_guard �����ڿ��� m1.lock()���� ȹ��


	// .lock() �� �ƴ� ������� ���ؽ� �� ����Ϸ��� ���� ȹ���ϼ���
	if (m2.try_lock())
	{

		// lock�� ���� ������ unlock �� lock_guard�� ����ϰ� �ʹ�!!
//		std::lock_guard<std::mutex> g2(m2); // ����
					// => �̹� lock �� ȹ���� m2�� ���ؼ�
					//	  �ٽ� m2.lock �ϰ� �˴ϴ�.

		std::lock_guard<std::mutex> g2(m2, std::adopt_lock);
					// => 2��° ���ڷ� �̹� lock �� ȹ���ߴٰ� �˷��� �մϴ�.
		
		
	}

}


int main()
{
	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}



