#include <iostream>
#include <thread>
#include <atomic>

//long x = 0; // 멀티스레드에 안전하지 않습니다.


std::atomic<long> x = 0;

void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
        //++x; // x.operator++() 이 실행됩니다.
               // => 이 함수가 lock-free로 구현되어 있습니다.

        //x.fetch_add(1); // 이렇게 해도 됩니다.
        x.fetch_add(1, std::memory_order_relaxed);
                        // => ++대신 이함수를 사용하면
                        //    memory_order 를 변경가능합니다.
                        // 디폴트는 "memory_order_seqcst"
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
