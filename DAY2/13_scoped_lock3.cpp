#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;


// ���� ���� �Դϴ�.
struct  Account
{
    std::mutex m;   // money �� ���������� ���� ���� mutex
    int money = 100;
};

void transfer(Account& acc1, Account& acc2, int cnt)
{
    // 2���̻��� mutex �� ���� lock ����

    // ��� 1. 
//  std::lock(acc1.m, acc2.m);  
//  std::lock_guard<std::mutex> g1(acc1.m, std::adopt_lock);
//  std::lock_guard<std::mutex> g2(acc2.m, std::adopt_lock);


    // ��� 2. std::scoped_lock ���
//  std::scoped_lock<std::mutex, std::mutex> g(acc1.m, acc1.m);

    // C++17 ���ʹ� ���ø��� Ÿ�� ���� ���������մϴ�.
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

