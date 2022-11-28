#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals;


// yield() 를 사용해서 sleep() 만들기
// system_clock : 
// high_resolution_clock : 가장 정밀한 시계
//                         현재 대부분 system_clock 과 동일
void mysleep(std::chrono::microseconds us)
{
    auto target = std::chrono::high_resolution_clock::now() + us;

    while (std::chrono::high_resolution_clock::now() < target)
        std::this_thread::yield();
}

int main()
{
    mysleep(1s);
}