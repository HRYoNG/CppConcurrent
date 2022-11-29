#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;         // 스레드가 하나의 뮤텍스를 2번 이상 lock 할수 없음.
                        // 한번만 가능.

std::recursive_mutex m; // 뮤텍스의 소유자는 다시 lock 할수 있다.
                        // 단, lock 을 수행한 횟수만큼 unlock 필요! 
int share_data = 0;

void foo()
{
    std::cout << "wait mutex lock" << std::endl;
    
    m.lock();
    m.lock(); // mutex 소유자가 다시 한번 lock
    
    std::cout << "acquire mutex lock" << std::endl;

    share_data = 100;
    std::cout << "using share_data" << std::endl;
    m.unlock();
    m.unlock();
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}





