#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>
#include <mutex>
using namespace std::literals;

// 45 page

void delay() { std::this_thread::sleep_for(20ms); }


// critical section : �Ѱ��� �����常 �����Ҽ� �ִ� ����
std::mutex m;

void foo(const std::string& name)
{
//  int x = 0; // ������� �Ѱ��� ����

    static int x = 0; // ��� �����尡 ����

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



