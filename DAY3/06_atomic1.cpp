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
        /*
        __asm
        {
            mov eax, x
            add eax, 1
            mov x, eax
        }
        */
        /*
        // �ذ�å 1. mutex ���� ����ؼ� ����ȭ
        m.lock();
        x = x + 1;
        m.unlock();
        */
        // �ذ�å 2. CPU �� �����ϴ� ����߿��� 
        //         "��Ƽ �ھ�� �����ϰ� 1�����ϴ� ��� ���"
        // ������ "lock" ���ξ� : �ϳ��� CPU �� �����ϴ� ����
        //                      �ٸ� CPU �� ���� �Ҽ� ����.
        __asm
        {
            lock inc x 
        }

        // lock - free ���
        // => OS �Ǵ� �� �����ϴ� ����ȭ�� ������� �ʰ�
        // => CPU ��ü�� �����ϴ� ����� ����ȭ �ϴ� ��
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
