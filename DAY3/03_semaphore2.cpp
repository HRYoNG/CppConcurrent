#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore> // C++20 의 도구 입니다.
using namespace std::literals;


// 템플릿 인자 : 최대 카운트
// 생성자 인자 : 카운트 초기값
// 규칙       : 최대 카운트 >= 카운트 >= 0

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
    
    sem.release();  // sem.count += 인자(디폴트값은 1)
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