#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// �ٽ� : �ڿ��� �����, �Լ��� ������ �ٿ��� ���� �ݳ��ϴ� �ڵ�� ������� ������
void f()
{
    // �ڿ� ȹ��...

    // �ڿ� ���

    // �ڿ� �ݳ�.. <<==== ���� �̷��� ���� ������
}

// �ذ�å : ������/�Ҹ��ڷ� �ڿ��� ���� �ϼ���..


std::mutex m;

void goo()
{
    m.lock();    
    std::cout << "using shared data" << std::endl;

    throw std::exception(); // ���� �߻�

    m.unlock();
}

void foo()
{
    try
    {
        goo();
    }
    catch (...)
    {
        std::cout << "�߻��� ���� ó�� �Ϸ�" << std::endl;
    }
}



int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



