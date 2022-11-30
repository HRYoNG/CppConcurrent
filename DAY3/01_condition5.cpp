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

        data_process = true;    // 데이타가 처리 되었음.
    }

    cv.notify_one();        // 신호를 다시 전달
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

    // 데이타 처리가 완료 될때 까지 대기
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul, [] {return data_process; });

    std::cout << "producer : 데이타 처리 완료 됨" << std::endl;
}



int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}