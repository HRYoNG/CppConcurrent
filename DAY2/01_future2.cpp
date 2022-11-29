#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 한 promise 객체를 다수의 스레드에서 같이 사용할수있나요 ?
// => 지금 예제를 참고 하세요..

void add(std::promise<int>& p, int a, int b)
{
    std::this_thread::sleep_for(1s);

    // 핵심 1. set_value() 는 한번만 가능합니다.
    p.set_value(a + b);
//  p.set_value(a + b); // 예외!!!

    // 즉, promise 는 1회용입니다.
    // 여러 스레드가 공유 안됩니다.
    // 여러 스레드가 공유하거나, 여러번 결과를 보내려면
    // 오늘 오후부터 배우는 동기화 기술을 직접 사용하세요..

    // 스레드 함수에서 결과 한개만 꺼내고 싶을때 : promise, packaged_task, async
    // 스레드 함수와 여러번 데이타 교환 : 다양한 동기화 도구를 직접 사용하세요
}

int main()
{
    std::promise<int> pm;

    // 핵심 2. promise 에서 future 는 한개만 꺼낼수 있습니다.
    std::future<int> ft = pm.get_future();
//  std::future<int> ft2 = pm.get_future(); // 예외!!

    // 핵심 3. future 객체는 복사 안됩니다.
//  std::future<int> ft2 = ft;  // error. 

    std::thread t(add, std::ref(pm), 10, 20);


    // 핵심 4. ft.get() 도 한번만 가능합니다.

    std::cout << ft.valid() << std::endl; // true
    int ret = ft.get();

    std::cout << ft.valid() << std::endl; // false
//  ret = ft.get(); // 예외 발생


    t.join();
}



