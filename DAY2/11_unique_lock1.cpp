#include <mutex>

// C++ 에서 mutex는 6개 입니다.
// C++ 에서 lock management 도구는 4개 입니다.

// 1. std::lock_guard : 가장 가볍고, 단순한 기능. 생성자와 소멸자만 있습니다.


// 2. std::unique_lock : 가장 기능이 많습니다.
//						std::condition_variable 을 사용하려면 필요 합니다.

// 3. std::shared_lock : shared_mutex 를 위한 도구. 
//						 생성자에서 lock_shared()
//						 소멸자에서 unlock_shared()

// 4. std::scoped_lock : 2개 이상의 뮤텍스를 동시에 lock 할때



std::mutex m;

int main()
{
	// lock_guard 를 사용하는 2가지 방법
	// 1. 생성자에서 lock 획득
	{
		std::lock_guard<std::mutex> lg(m);
	}

	// 2. 이미 lock 획득한 상태의 뮤텍스 관리
	if (m.try_lock())
	{
		std::lock_guard<std::mutex> lg(m, std::adopt_lock);
	}	
}



