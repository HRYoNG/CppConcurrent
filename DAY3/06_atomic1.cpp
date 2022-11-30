#include <iostream>
#include <thread>
#include <mutex>
#include "chronometry.h"

constexpr unsigned int cnt = 1000000;


long x = 0; // ��� �����尡 ����.

void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
    //    x = x + 1;  

        // �� ������ �Ʒ� 3���� ������� �����մϴ�.
        __asm
        {
            mov eax, x
            add eax, 1
            mov x, eax
        }
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
