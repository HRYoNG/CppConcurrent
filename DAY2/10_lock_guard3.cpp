#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m1;
std::mutex m2;

void foo()
{
	std::lock_guard<std::mutex> g1(m1); 
			// => lock_guard 생성자에서 m1.lock()으로 획득


	// .lock() 이 아닌 방법으로 뮤텍스 를 사용하려면 직접 획득하세요
	if (m2.try_lock())
	{

		// lock은 직접 했지만 unlock 은 lock_guard을 사용하고 싶다!!
//		std::lock_guard<std::mutex> g2(m2); // 버그
					// => 이미 lock 을 획득한 m2에 대해서
					//	  다시 m2.lock 하게 됩니다.

		std::lock_guard<std::mutex> g2(m2, std::adopt_lock);
					// => 2번째 인자로 이미 lock 을 획득했다고 알려야 합니다.
		
		
	}

}


int main()
{
	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}



