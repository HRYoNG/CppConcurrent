#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

std::condition_variable cv;

// �Ϲ������� condition_variable �� flag ������ ���� ����ؾ� �մϴ�.
bool data_ready = false;




void consumer()
{
    std::this_thread::sleep_for(10ms);

    std::unique_lock<std::mutex> ul(m);

//  cv.wait(ul);       // ������ ��ȣ�� ���!
//  cv.wait(ul, �Լ�);  // 1. �Լ��� ���� �����ϰ�
                       // 2. �Լ� ����� �����̸� ��ȣ�� �ö��� ���
                       // 3. �Լ� ����� ���̸� ��� ����.

    cv.wait(ul, [] { return data_ready; } );

    std::cout << "consume : " << shared_data << std::endl;
}



void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;

        data_ready = true;  // ����Ÿ �غ� �Ǿ���.!
                            // flag �� ������
    }
    cv.notify_one();        // ��ȣ�� �ְ� �˴ϴ�.
}



int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}