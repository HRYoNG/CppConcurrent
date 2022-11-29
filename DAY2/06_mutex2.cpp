#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

std::mutex m;

int share_data = 0; // 파일같은 공유 자원으로 생각하세요..


void foo()
{
//  m.lock();   // 뮤텍스를 획득하지 못한 스레드는 대기해야 합니다.
                // 소유자가 unlock 할때 까지

    if (m.try_lock()) // 획득하지 못한 경우 false 반환.!
    {
        // 뮤텍스를획득한 경우, 공유자원 사용하고 unlock()
        share_data = 100;

        m.unlock();
    }
    else
    {
        // 뮤텍스를 획득하지 못한 경우. 
    }
}



int main()
{
    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();
}



