#include <iostream>
#include <thread>
#include <atomic>

//long x = 0; // ��Ƽ�����忡 �������� �ʽ��ϴ�.


std::atomic<long> x = 0;

void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
        //++x; // x.operator++() �� ����˴ϴ�.
               // => �� �Լ��� lock-free�� �����Ǿ� �ֽ��ϴ�.

        //x.fetch_add(1); // �̷��� �ص� �˴ϴ�.
        x.fetch_add(1, std::memory_order_relaxed);
                        // => ++��� ���Լ��� ����ϸ�
                        //    memory_order �� ���氡���մϴ�.
                        // ����Ʈ�� "memory_order_seqcst"
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
