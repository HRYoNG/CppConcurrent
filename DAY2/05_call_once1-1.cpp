#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// 1. std::once_flag 변수를 전역으로 한개만 만듭니다.
std::once_flag flag;

void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

void foo()
{
    std::cout << "start foo" << std::endl;

    // 2. 초기화 함수 호출시 아래처럼 직접 호출하지 말고 call_once 사용하세요
    // init(10, 3.4);  
    std::call_once(flag, init, 10, 3.4);
        // 

    std::cout << "finish foo" << std::endl;
}



int main()
{
    std::thread t1(&foo);
    std::thread t2(&foo);
    t1.join();
    t2.join();
}



