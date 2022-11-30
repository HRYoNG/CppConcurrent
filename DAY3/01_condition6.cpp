#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

// ���� ��� "������(Writer) 1��, �Һ���(Reader) 3��" ���� �Դϴ�.

std::shared_mutex m;

int share_data = 0;


// "Write �Ŀ� Read" �Ҽ� �ֵ��� condition_variable����
bool data_ready = false;

//std::condition_variable cv; // unique_lock ���θ� ��� ���� �մϴ�

std::condition_variable_any cv; // unique_lock �� �ƴ϶� 
                                // lock/unlock �� �ִ� ��� 
                                // lock management ������ ��밡���մϴ�.
                                // ��κ� shared_lock �� ����մϴ�.


void Writer()
{
    while (1)
    {
        {
            std::lock_guard<std::shared_mutex> g(m);

            share_data = share_data + 1;
            std::cout << "Writer : " << share_data << std::endl;
            std::this_thread::sleep_for(1s);
            
            data_ready = true;
        }
        cv.notify_one();

        std::this_thread::sleep_for(10ms);
    }
}



void Reader(const std::string& name)
{
    while (1)
    {
        {
            // std::condition_variable_any �� shared_lock �� ��밡���մϴ�.
            std::shared_lock<std::shared_mutex> g(m);   

            cv.wait(g, []() { return data_ready; } );

            std::cout << "Reader(" << name << ") : " << share_data << std::endl;
            std::this_thread::sleep_for(500ms);
        }
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



