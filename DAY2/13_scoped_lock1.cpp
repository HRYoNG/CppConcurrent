#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;


// 은행 계좌 입니다.
struct  Account
{
    std::mutex m;   // money 의 동시접근을 막기 위한 mutex
    int money = 100;
};

void transfer(Account& acc1, Account& acc2, int cnt)
{
    acc1.m.lock();

    std::this_thread::sleep_for(100ms); // deadlock 을 만들기 위한
                                        // 의도적인 코드
   
    acc2.m.lock();
    acc1.money -= cnt;
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

    acc2.m.unlock();
    acc1.m.unlock();
}

int main()
{
    Account kim, lee;
    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    t1.join();
    t2.join();
}

