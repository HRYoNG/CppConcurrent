#include <iostream>
#include <thread>

void foo() {}

int main()
{
//  std::thread t1(&foo);   // ������ ������
//  t1.join(); // ok.. 


    std::thread t2; // �Լ��� �������� �ʾҽ��ϴ�.
                    // ������ �������� �ʽ��ϴ�

    t2.join();  // ���� �߻�!



}
