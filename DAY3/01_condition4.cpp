#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

std::condition_variable cv;

// 일반적으로 condition_variable 은 flag 변수와 같이 사용해야 합니다.
bool data_ready = false;




void consumer()
{
    std::this_thread::sleep_for(10ms);

    std::unique_lock<std::mutex> ul(m);

//  cv.wait(ul);       // 무조건 신호를 대기!
//  cv.wait(ul, 함수);  // 1. 함수를 먼저 실행하고
                       // 2. 함수 결과가 거짓이면 신호가 올때를 대기
                       // 3. 함수 결과가 참이면 대기 안함.

    cv.wait(ul, [] { return data_ready; } );

    std::cout << "consume : " << shared_data << std::endl;
}



void producer()
{
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;

        data_ready = true;  // 데이타 준비 되었음.!
                            // flag 를 변경후
    }
    cv.notify_one();        // 신호를 주게 됩니다.
}



int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}