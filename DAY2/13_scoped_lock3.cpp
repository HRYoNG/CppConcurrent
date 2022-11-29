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
    // 2개이상의 mutex 에 대한 lock 관리

    // 방법 1. 
//  std::lock(acc1.m, acc2.m);  
//  std::lock_guard<std::mutex> g1(acc1.m, std::adopt_lock);
//  std::lock_guard<std::mutex> g2(acc2.m, std::adopt_lock);


    // 방법 2. std::scoped_lock 사용
//  std::scoped_lock<std::mutex, std::mutex> g(acc1.m, acc1.m);

    // C++17 부터는 템플릿의 타입 인자 생략가능합니다.
    std::scoped_lock g(acc1.m, acc1.m);

    acc1.money -= cnt;
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

}






int main()
{
    Account kim, lee;
    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    t1.join();
    t2.join();
}

