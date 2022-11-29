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


/*
template <class _Mutex>
class lock_guard 
{ 
public:
	explicit lock_guard(_Mutex& _Mtx) : _MyMutex(_Mtx) { 
		_MyMutex.lock();
	}

	lock_guard(_Mutex& _Mtx, adopt_lock_t) : _MyMutex(_Mtx) {} // construct but don't lock

	~lock_guard() noexcept {
		_MyMutex.unlock();
	}

	lock_guard(const lock_guard&) = delete;
	lock_guard& operator=(const lock_guard&) = delete;

private:
	_Mutex& _MyMutex;
};
*/
// 6개 mutex 모두 lock_guard 사용가능하나요
// => 네. 6개 모두 lock/unlock 있으므로 가능합니다.

// recursive mutex를 lock_guard에 넣어줘도 될까요?
// => 네. 가능하고, 그렇게 해야 합니다.

// shared_mutex 를 넣을수 있나요 ?
// => 네. 하지만, shared_mutex 만의 특징을 사용할수 없습니다.
// => 사용하려면 이어지는 예제들..