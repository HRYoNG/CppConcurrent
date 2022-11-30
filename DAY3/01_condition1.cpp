#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;


// 아래 코드는 "mutex" 로 동기화 자원의 동시접근을 막는 코드 입니다.

// 1. mutex 로 동시접근은 막고 있습니다.
// 2. 하지만 생성자 보다 소비자가 먼저 소비하는 문제가 있습니다.
//    "생산후 소비"를 하게 할수 없을까요 ??

std::mutex m;
int shared_data = -1; // 쓰레기값

void consumer()
{
    std::lock_guard<std::mutex> lg(m);
    std::cout << "consume : " << shared_data << std::endl;
}
void producer()
{
    std::this_thread::sleep_for(10ms);
    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}