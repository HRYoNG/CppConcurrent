#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

std::condition_variable cv;

// 아래 코드의 문제점 
// => 생산자가 소비자 보다 먼저 도착 합니다.
// => 소비자가 wait 하기 전에 생성자가 signal 을 보내게 됩니다.

void consumer()
{
    std::this_thread::sleep_for(10ms);

    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);    // <= 이미 cv.notify_xxx() 한후에 
                    // <= 늦게 도착해서 wait 하고 있습니다.
                    //    다시 cv.notify_xxx() 를 할때 까지 대기하게 됩니다.
                    // 해결책은 "conditio4" 에서!!

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{

    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }

    cv.notify_one();
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}