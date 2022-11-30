#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

std::condition_variable cv;


bool data_ready   = false;
bool data_process = false;



void consumer()
{
    std::this_thread::sleep_for(10ms);

    {
        std::unique_lock<std::mutex> ul(m);

        cv.wait(ul, [] { return data_ready; });

        std::cout << "consume : " << shared_data << std::endl;

        data_process = true;    // ����Ÿ�� ó�� �Ǿ���.
    }

    cv.notify_one();        // ��ȣ�� �ٽ� ����
}






void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;

        data_ready = true;  
       
    }
    cv.notify_one();

    // ����Ÿ ó���� �Ϸ� �ɶ� ���� ���
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul, [] {return data_process; });

    std::cout << "producer : ����Ÿ ó�� �Ϸ� ��" << std::endl;
}



int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}