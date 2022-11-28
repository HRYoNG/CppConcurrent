#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

void foo(int a, int b)
{
    std::cout << "foo : " << a << ", " << b << std::endl;

    std::this_thread::sleep_for(3s);
}  

int main()
{
    // 핵심 1. std::thread 는 join 또는 detach 필요
//  std::thread t1(&foo, 10, 20);
//  std::thread t2(&foo, 10, 20);

//  t1.join();
//  t2.join();

    // 핵심 2. C++20 jthread 는 소멸자에서 자동으로 join 수행
    std::jthread jt1(&foo, 10, 20);
    std::jthread jt2(&foo, 10, 20);

} // <== 이순간 jt1, jt2가 파괴, 소멸자에서 자동으로 .join() 호출

// g++ 소스.cpp -std=c++20