#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// QA 1. 퓨처객체도 프로미스 객체에서 받아와서 생성되는 건데 왜 굳이 프로미스만 쓰지않고 
// 퓨처객체를 만들어서 사용하는 구조로 된 건지 혹시 이유가 있나요?
// promise - future
// packaged_task - future
// async - future

// QA 2. ft.get() 이 무한루프 돌면서 대기하나요
// => 구현에 따라 다릅니다. C++ 표준에는 구현을 언급하지 않았습니다.
// => 대부분은 무한 루프는 아니로 CPU cycle 을 적게 사용하는 구현을 사용합니다.

// QA 3. 타임아웃도 걸수있나요 ?
// => 지금 예제!!!

void add(std::promise<int>& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::ref(pm), 10, 20);

    int ret = ft.get();

    t.join();
}



