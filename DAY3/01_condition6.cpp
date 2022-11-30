#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

// 어제 배운 "생산자(Writer) 1개, 소비자(Reader) 3개" 예제 입니다.

std::shared_mutex m;

int share_data = 0;


// "Write 후에 Read" 할수 있도록 condition_variable도입
bool data_ready = false;

//std::condition_variable cv; // unique_lock 으로만 사용 가능 합니다

std::condition_variable_any cv; // unique_lock 뿐 아니라 
                                // lock/unlock 이 있는 모든 
                                // lock management 도구와 사용가능합니다.
                                // 대부분 shared_lock 과 사용합니다.


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
            // std::condition_variable_any 는 shared_lock 도 사용가능합니다.
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



