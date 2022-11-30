#include <iostream>
#include <thread>
#include <mutex>
#include "chronometry.h"

constexpr unsigned int cnt = 1000000;


long x = 0; // 모든 스레드가 공유.

void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
    //    x = x + 1;  

        // 위 한줄은 아래 3줄의 어셈블리를 생성합니다.
        /*
        __asm
        {
            mov eax, x
            add eax, 1
            mov x, eax
        }
        */
        /*
        // 해결책 1. mutex 등을 사용해서 동기화
        m.lock();
        x = x + 1;
        m.unlock();
        */
        // 해결책 2. CPU 가 제공하는 명령중에서 
        //         "멀티 코어에서 안전하게 1증가하는 명령 사용"
        // 인텔의 "lock" 접두어 : 하나의 CPU 가 접근하는 동안
        //                      다른 CPU 는 접근 할수 없다.
        __asm
        {
            lock inc x 
        }

        // lock - free 기술
        // => OS 또는 언어가 제공하는 동기화를 사용하지 않고
        // => CPU 자체가 제공하는 기술로 동기화 하는 것
    }
}



int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
    std::cout << x << std::endl;
}
