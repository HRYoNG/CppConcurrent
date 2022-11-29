#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

void foo(std::promise<int>& p)
{
    std::cout << "start foo" << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "finish foo" << std::endl;
    p.set_value(10);
}
int main()
{
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    std::thread t(foo, std::ref(p));
    t.detach();

//  ft.get();
}
// async 가 반환 하는 future   : 소멸자에서 "get()" 합니다.
// promise 가 반환 하는 future : 소멸자에서 "get()" 하지 않습니다.
//                              대기 안합니다.



