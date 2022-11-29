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
//  acc1.m.lock();
//  acc2.m.lock();

    // 2개 이상의 뮤텍스를 lock 할때는
    // 따로 lock 을 하지말고
    // "deadlock 회피 기술을 사용한 std::lock()" 을 사용해야 합니다.
    std::lock(acc1.m, acc2.m);  // 모두 획득할때 까지 대기.


    // 2개의 뮤텍스를 lock 을 했으므로, unlock 만 자동화 합니다.
    std::lock_guard<std::mutex> g1(acc1.m, std::adopt_lock);
    std::lock_guard<std::mutex> g2(acc2.m, std::adopt_lock);

    acc1.money -= cnt;
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

//    acc2.m.unlock();
//    acc1.m.unlock();
}

int main()
{
    Account kim, lee;
    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    t1.join();
    t2.join();
}

