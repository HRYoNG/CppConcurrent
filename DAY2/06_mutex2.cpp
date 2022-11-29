#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

std::mutex m;

int share_data = 0; // ���ϰ��� ���� �ڿ����� �����ϼ���..


void foo()
{
//  m.lock();   // ���ؽ��� ȹ������ ���� ������� ����ؾ� �մϴ�.
                // �����ڰ� unlock �Ҷ� ����

    if (m.try_lock()) // ȹ������ ���� ��� false ��ȯ.!
    {
        // ���ؽ���ȹ���� ���, �����ڿ� ����ϰ� unlock()
        share_data = 100;

        m.unlock();
    }
    else
    {
        // ���ؽ��� ȹ������ ���� ���. 
    }
}



int main()
{
    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();
}



