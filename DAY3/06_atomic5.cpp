#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
using namespace std::literals;

void init()
{
    std::cout << "start init" << std::endl;
    
    std::this_thread::sleep_for(5s);

    std::cout << "end init" << std::endl;
}

void foo()
{
    init();

    std::cout << std::this_thread::get_id() << "finish foo" << std::endl;
}

int main()
{
    std::thread t1(&foo);
    std::thread t2(&foo);

    t1.join();
    t2.join();
}

