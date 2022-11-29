#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

class Machine
{
//  std::mutex m; // 2¹ø È¹µæ ¾ÈµÊ

    std::recursive_mutex m; // 2¹ø ÀÌ»ó È¹µæ °¡´É.

    int shared_data = 0;
public:
    void f1()
    {
        m.lock();
        shared_data = 100;
        m.unlock();
    }
    void f2()
    {
        m.lock();
        shared_data = 200;
        m.unlock();
    }
    void f3()
    {
        m.lock();

        shared_data = 300;
        f1();

        m.unlock();

    }
};



int main()
{
    Machine m;
    std::thread t1(&Machine::f1, &m);
    std::thread t2(&Machine::f2, &m);
    t1.join();
    t2.join();
}



