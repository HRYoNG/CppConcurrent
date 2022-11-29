#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::timed_mutex m;

int main()
{
    std::unique_lock<std::timed_mutex> u1;  // 연결된 mutex 없음
    std::unique_lock<std::timed_mutex> u2(m);// m.lock() 수행됨

    // 핵심 1. 복사와 move
//  u1 = u2;            // error. 복사 또는 대입 안됨
    u1 = std::move(u2); // ok.    move 생성, move 대입은 가능


    // 핵심 2. lock 을 소유 했는지 조사
    std::cout << u1.owns_lock() << std::endl; 

    if (u1)
        std::cout << "acquire" << std::endl;

    // 핵심 3. unlock 을 위한 멤버 함수 제공.
    u1.unlock();

    std::cout << u1.owns_lock() << std::endl;  

    // 핵심 4. 생성자가 아니라 멤버 함수로 명시적으로 lock 을 다시 할수도 있다.
    if (u1.try_lock_for(2s))
    {
        //....
        u1.unlock();
    }

    u1.release();
}



