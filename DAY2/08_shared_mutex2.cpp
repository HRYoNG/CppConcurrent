#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex> // C++17
#include <string_view>
using namespace std::literals;


// 1. ���� ����, �ٸ� ������� ������ ����� �Ѵ�.
// 2. ���� ����, �ٸ� ������� ���� ����� �Ѵ�.
// 3. �д� ����, �ٸ� ������� ���� ����� �Ѵ�.
// 
// 4. �д� ����, �ٸ� �����嵵 ������ �־�� �Ѵ�. <<=== �ٽ� !!


// shared_mutex ���� ���

// m.lock() �ϸ� : �ٸ� �������� m.lock(), m.lock_shared() ��� ��� 
//              => ���� ������, "����, �б�" ��� ����
// 
// m.lock_shared() �ϸ� : �ٸ� ������� m.lock()�� ���
//                       �ٸ� �������� m.lock_shared()�� ��� ����
//              => �д� ���ȿ�, "����� ����, �б�� ����"
// 
// Write  : m.lock(),        m.unlock()
// Reader : m.lock_shared(), m.unlock_shared(), 




//std::mutex m;

std::shared_mutex m;

int share_data = 0;


void Writer()
{
    while (1)
    {
        m.lock();
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}


void Reader(const std::string& name)
{
    while (1)
    {
        m.lock_shared();
        
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);
        m.unlock_shared();

        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    std::thread t1(Writer);
    std::thread t2(Reader, "A");
    std::thread t3(Reader, "B");
    std::thread t4(Reader, "C");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}



