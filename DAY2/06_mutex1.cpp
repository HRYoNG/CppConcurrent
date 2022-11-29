#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>
#include <mutex>
using namespace std::literals;

// 45 page

void delay() { std::this_thread::sleep_for(20ms); }


// critical section : 한개의 스레드만 진입할수 있는 구간
std::mutex m;

void foo(const std::string& name)
{
//  int x = 0; // 스레드당 한개의 변수

    static int x = 0; // 모든 스레드가 공유

    for (int i = 0; i < 10; i++)
    {
        m.lock();
        //----------------------------------------------
        x = 100;   delay();
        x = x + 1; delay();
        std::cout << name << " : " << x << std::endl; delay();
        //-------------------
        m.unlock();
    }
}







int main()
{
    std::thread t1(foo, "A");
    std::thread t2(foo, "\tB");
    t1.join();
    t2.join();
}



