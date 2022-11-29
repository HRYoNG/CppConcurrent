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

//  int ret = ft.get(); // 결과가 나올때 까지 무한히 대기 합니다.


    std::future_status ret = ft.wait_for(2s); // 2초까지만 대기

    if (ret == std::future_status::ready)
    {
        std::cout << "set_value() 가 되어서 결과 준비됨" << std::endl;
        std::cout << ft.get() << std::endl; // 결과가 이미 있으므로
                                            // 대기 하지 않음
    }
    else if (ret == std::future_status::timeout)
    {
        std::cout << "timeout" << std::endl;
    }
    else if (ret == std::future_status::deferred)
    {
        std::cout << "스레드 아직 실행안됨" << std::endl;
        std::cout << "async()가 반환된 future 만의 특징" << std::endl;
    }







    t.join();
}



