#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::timed_mutex m;

int main()
{
    std::unique_lock<std::timed_mutex> u1;  // ����� mutex ����
    std::unique_lock<std::timed_mutex> u2(m);// m.lock() �����

    // �ٽ� 1. ����� move
//  u1 = u2;            // error. ���� �Ǵ� ���� �ȵ�
    u1 = std::move(u2); // ok.    move ����, move ������ ����


    // �ٽ� 2. lock �� ���� �ߴ��� ����
    std::cout << u1.owns_lock() << std::endl; 

    if (u1)
        std::cout << "acquire" << std::endl;

    // �ٽ� 3. unlock �� ���� ��� �Լ� ����.
    u1.unlock();

    std::cout << u1.owns_lock() << std::endl;  

    // �ٽ� 4. �����ڰ� �ƴ϶� ��� �Լ��� ��������� lock �� �ٽ� �Ҽ��� �ִ�.
    if (u1.try_lock_for(2s))
    {
        //....
        u1.unlock();
    }

    u1.release();
}



