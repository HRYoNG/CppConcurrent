#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

     
void foo()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "foo : " << i << std::endl;
        std::this_thread::sleep_for(100ms);
    }
}

int main()
{
//  foo();  // 주스레드가 그냥 실행!!

    // 핵심 1. 스레드를 생성하는 방법.
    std::thread t1(&foo);   // 이순간 새로운 스레드가 생성되어서
                            // foo 실행.
                            // 별도의 "start()"같은 함수 없습니다.
                            // 객체만 생성하면 됩니다.
}

