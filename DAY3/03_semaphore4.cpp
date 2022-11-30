#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore> // C++20 의 도구 입니다.
using namespace std::literals;


//std::counting_semaphore<1> sem(1);
                // => 최대 크기가 1인 세마 포어
                // => 소유권 없는 mutex 와 유사해 보입니다.
                // mutex     : 소유자만 unlock 가능
                // semaphore : 누구나 카운트 증가 가능
                //             따라서, 독점은 아님.!!
std::binary_semaphore sem(1); // 위와 동일. 



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