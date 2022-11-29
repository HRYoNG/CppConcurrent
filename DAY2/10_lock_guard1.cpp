#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// 54 page

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



