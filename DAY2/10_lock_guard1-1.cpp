#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// �ذ�å : ������/�Ҹ��ڷ� �ڿ��� ���� �ϼ���..


std::mutex m;

void goo()
{
//    m.lock();

    std::lock_guard<std::mutex> g(m); // �����ڿ��� m.lock()�մϴ�.

    std::cout << "using shared data" << std::endl;

    throw std::exception(); // ���� �߻�
                // stack unwiniding(���� Ǯ��)
                // => ���� �߻��� ���������� �����ϰ� �ı� �ǰ� catch �� �̵�
                // => ��, g�� �Ҹ��ڰ� ȣ��ǰ� catch�� �̵�.

//    m.unlock();

}   // <= g �� �ı��Ǵµ�, �Ҹ��ڿ��� unlock() �մϴ�.



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



