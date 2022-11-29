#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;     // m.lock()
                    // m.try_lock() 의 2가지 방법 제공

std::timed_mutex m; // 위 2개 + 2개의 방법을 추가로 제공
                    // m.try_lock_for( 시간 동안 )
                    // m.try_lock_until(시간 까지)
                    //    => 시간까지 는 어제 sleep_until()예제참고


int share_data = 0;

void foo()
{
    //m.lock();
    //if ( m.try_lock() )

    if ( m.try_lock_for(2s) ) 
    {
        share_data = 100;
        std::cout << "using share_data" << std::endl;
        std::this_thread::sleep_for(3s);
        m.unlock();
    }
    else
    {
        std::cout << "뮤텍스 획득 실패" << std::endl;
    }
}
int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}


// C++ 표준 뮤텍스는 6개 입니다

// std::mutex          std::recursive_mutex        std::shared_mutex
// std::timed_mutex    std::timed_recursive_mutex  std::timed_shared_mutex
