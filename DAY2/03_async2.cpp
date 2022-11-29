#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
    std::cout << "add : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);
    return a + b;
}

int main()
{
//  std::future<int> ft = std::async( add, 10, 20);

    // 핵심 1. launch 옵션
    // std::launch::async : 비동기로 실행해 달라. 새로운 스레드생성
    // std::launch::deferred : 지연된 실행. ft.get() 할때 실행됨
    //                          주스레드가 직접 호출
    // std::future<int> ft = std::async(std::launch::async, add, 10, 20);
    // std::future<int> ft = std::async(std::launch::deferred, add, 10, 20);

    


    // 핵심 2. launch 옵션은 OR(|) 가능합니다.
    // => 스레드가 지원되는 시스템에서는 "스레드"로 수행
    // => 스레드가 지원되지 않은 시스템에서는 "지연된실행"으로 수행
    //std::future<int> ft = 
    //    std::async(std::launch::async | std::launch::deferred, add, 10, 20);


    // 핵심 3. launch 옵션을 생략하면
    // => "std::launch::async | std::launch::deferred" 사용

    std::future<int> ft = std::async( add, 10, 20);





    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    int ret = ft.get();

    std::cout << "result : " << ret << std::endl;
}



