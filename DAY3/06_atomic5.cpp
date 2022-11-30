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

/*
std::once_flag flag;

void foo()
{
    // ���� ������ �����尡 init() ȣ��
    // ���߿� ������ ������� init() ���� ���� ��� 
    std::call_once(flag, init);

    std::cout << std::this_thread::get_id() << "finish foo" << std::endl;
}
*/
// blocking ���� ���� call_once �� ����� ���ô�.

template<typename F>
void call_once_nonblock(std::atomic<bool>& flag, F func)
{
    bool b = false;

    if (flag.compare_exchange_weak(b, true))
    {
        func();
    }
}

std::atomic<bool> flag;

void foo()
{
//     std::call_once(falg, init); C++ ǥ��, �ʰ� �����ϸ� block
    call_once_nonblock(flag, init);

    std::cout << std::this_thread::get_id() << "finish foo " << std::endl;
}




int main()
{
    std::thread t1(&foo);
    std::thread t2(&foo);

    t1.join();
    t2.join();
}

