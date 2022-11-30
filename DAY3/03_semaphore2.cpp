#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore> // C++20 �� ���� �Դϴ�.
using namespace std::literals;


// ���ø� ���� : �ִ� ī��Ʈ
// ������ ���� : ī��Ʈ �ʱⰪ
// ��Ģ       : �ִ� ī��Ʈ >= ī��Ʈ >= 0

std::counting_semaphore<3> sem(3);

void Download(std::string name)
{
    sem.acquire();  // if ( sem.count == 0 ) wait
                    // else --(sem.count); 

    for (int i = 0; i < 100; i++)
    {
        std::cout << name;
        std::this_thread::sleep_for(30ms);
    }
    std::cout << "\n finish " << name << std::endl;
    
    sem.release();  // sem.count += ����(����Ʈ���� 1)
}



int main()
{
    std::thread t1(Download, "1");
    std::thread t2(Download, "2");
    std::thread t3(Download, "3");
    std::thread t4(Download, "4");
    std::thread t5(Download, "5");

    t1.join();    t2.join();
    t3.join();    t4.join();
    t5.join();
}