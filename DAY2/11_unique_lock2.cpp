#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex       m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

int main()
{
    // 핵심 1. 생성 방법
    std::unique_lock<std::mutex> u1;     // 아직 mutex 연결안됨
    std::unique_lock<std::mutex> u2(m1); // 생성자에서 m1.lock()                 
    std::unique_lock<std::mutex> u3(m2, std::try_to_lock);
                                        // 생성자에서 m2.try_lock()
                                        // lock 을 획득하지 못해도 대기 안함

    // 핵심 2. lock 을 소유 했는지 조사
    if (u3.owns_lock())
        std::cout << "acquire lock" << std::endl;
    else
        std::cout << "fail to lock" << std::endl;


    // 핵심 3. 이미 획득한 mutex 에 대해 unlock 기능만 사용하는 경우
    m3.lock();
    std::unique_lock<std::mutex> u4(m3, std::adopt_lock);   


    // 핵심 4. 생성자에서 lock 하지말고, 나중에 lock 을 할 경우
    // => 또한, timed_mutex 가 가진 try_lock_for 를
    //    unique_ptr도 제공
    std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock);
    auto ret = u5.try_lock_for(2s);


    // 핵심 5. timed_mutex 를 전달하면 2번째 인자로 chrono 타입 전달 가능

    std::unique_lock<std::timed_mutex> u6(tm2, 2s);  // tm2.try_lock_for(2s) 사용
    std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s);
    // tm3.try_lock_until() 사용
}
