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
//  foo();  // �ֽ����尡 �׳� ����!!

    // �ٽ� 1. �����带 �����ϴ� ���.
    std::thread t1(&foo);   // �̼��� ���ο� �����尡 �����Ǿ
                            // foo ����.
                            // ������ "start()"���� �Լ� �����ϴ�.
                            // ��ü�� �����ϸ� �˴ϴ�.
}

