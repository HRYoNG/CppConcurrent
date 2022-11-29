#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// promise
// => 생성된 스레드가 "값" 과 "예외" 를 부모 스레드에게 전달할수 있는 도구
// => future 객체를 통해서 "값"과 "예외"를 대기 할수 있다.


void divide(std::promise<int>& p, int a, int b)
{
    try
    {
        if (b == 0)
        {
            throw std::runtime_error("divide by zero");
        }
        p.set_value(a / b);
    }
    catch (...)
    {
        // 현재 발생된 예외를 promise 를 통해서 
        // 주스레드(future 객체를 소유한 스레드)에 전달합니다.
        p.set_exception( std::current_exception() );
    }
}

int main()
{
    std::promise<int> pm;
    std::future<int>  ft = pm.get_future();

    std::thread t(divide, std::ref(pm), 10, 0 );

    try
    {
        int ret = ft.get();
    }
    catch (...)
    {
        std::cout << "스레드가 수행중에 예외 발생" << std::endl;
    }

    t.join();
}



