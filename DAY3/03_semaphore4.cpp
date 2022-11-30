#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore> // C++20 �� ���� �Դϴ�.
using namespace std::literals;


//std::counting_semaphore<1> sem(1);
                // => �ִ� ũ�Ⱑ 1�� ���� ����
                // => ������ ���� mutex �� ������ ���Դϴ�.
                // mutex     : �����ڸ� unlock ����
                // semaphore : ������ ī��Ʈ ���� ����
                //             ����, ������ �ƴ�.!!
std::binary_semaphore sem(1); // ���� ����. 



void Download(std::string name)
{
    sem.acquire();  

    for (int i = 0; i < 100; i++)
    {
        std::cout << name;
        std::this_thread::sleep_for(30ms);
    }
    std::cout << "\n finish " << name << std::endl;

    sem.release();  
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