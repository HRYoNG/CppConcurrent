#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;         // �����尡 �ϳ��� ���ؽ��� 2�� �̻� lock �Ҽ� ����.
                        // �ѹ��� ����.

std::recursive_mutex m; // ���ؽ��� �����ڴ� �ٽ� lock �Ҽ� �ִ�.
                        // ��, lock �� ������ Ƚ����ŭ unlock �ʿ�! 
int share_data = 0;

void foo()
{
    std::cout << "wait mutex lock" << std::endl;
    
    m.lock();
    m.lock(); // mutex �����ڰ� �ٽ� �ѹ� lock
    
    std::cout << "acquire mutex lock" << std::endl;

    share_data = 100;
    std::cout << "using share_data" << std::endl;
    m.unlock();
    m.unlock();
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}





