#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore> // C++20 의 도구 입니다.
using namespace std::literals;

// mutex     : 자원의 독점. 소유권 개념 있음. 소유자(lock한 스레드)만 unlock() 가능
// semaphore : 자원의 한정적 공유. 소유권 개념 없음. 누구나 카운트 증가/감소 가능

std::counting_semaphore<3> sem(3);
//std::counting_semaphore<3> sem(0);

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

//  sem.release();  // sem.count += 인자(디폴트값은 1)
}



int main()
{
    std::thread t1(Download, "1");
    std::thread t2(Download, "2");
    std::thread t3(Download, "3");
    std::thread t4(Download, "4");
    std::thread t5(Download, "5");
  
//  std::this_thread::sleep_for(7s);
    std::this_thread::sleep_for(2s);

    std::cout << "main - sem.release()" << std::endl;

    //sem.release();
    sem.release(2);



    t1.join();    t2.join();
    t3.join();    t4.join();
    t5.join();
}