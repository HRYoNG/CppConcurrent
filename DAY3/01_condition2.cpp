#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;


std::mutex m;
int shared_data = -1; 

// 1. condition_variable 타입의 전역변수를 생성합니다.
std::condition_variable cv;


void consumer()
{
    // 2. 신호를 대기하는 스레드는  unique_lock 으로 뮤텍스 획득후 
    //    신호를 대기 합니다.
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);    // 1. ul.unlock() 으로 lock 을 풀고
                    // 2. cv 에 대해서 신호가 올때 까지 대기 합니다
                    // 3. 신호가 오면 깨어난후, ul.lock() 으로 다시
                    //    뮤텍스 획득후.. 다음 코드 실행


    std::cout << "consume : " << shared_data << std::endl;
}




void producer()
{
    std::this_thread::sleep_for(10ms);
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    // 3. 신호를 주는 스레드는 unique_lock 을 사용하지 않아도 됩니다.
    // 공유자원이 준비 되면 신호를 주면 됩니다.
    // 주의사항은 "신호를 주기전에 unlock" 하고 신호를 주세요
    cv.notify_one();
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}