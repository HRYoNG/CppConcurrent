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
//  acc1.m.lock();
//  acc2.m.lock();

    // 2�� �̻��� ���ؽ��� lock �Ҷ���
    // ���� lock �� ��������
    // "deadlock ȸ�� ����� ����� std::lock()" �� ����ؾ� �մϴ�.
    std::lock(acc1.m, acc2.m);  // ��� ȹ���Ҷ� ���� ���.


    // 2���� ���ؽ��� lock �� �����Ƿ�, unlock �� �ڵ�ȭ �մϴ�.
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

