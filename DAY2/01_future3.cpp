#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}
int main()
{
    std::promise<int> pm;
    
    std::future<int> ft = pm.get_future();

    // 핵심1 : future 는 한번만 꺼낼수 있고, 복사도 안됩니다.
//  std::future<int> ft2 = pm.get_future(); // 예외
//  std::future<int> ft2 = ft; // error.

    // 핵심 2. future 에서 shared_future를 꺼낼수 있습니다
    // => 한번만 꺼낼수 있습니다.
    // => 하지만, shared_future 는 복사 가능합니다.
    std::shared_future<int> sf1 = ft.share();
//  std::shared_future<int> sf2 = ft.share(); // 예외
    std::shared_future<int> sf2 = sf1;
    std::shared_future<int> sf3 = sf1;
    
    std::thread t(add, std::ref(pm), 10, 20);

    // 핵심 3. 하나의 promise 에 대해서 3개의 "shared_future"가 있으면
    // 3개의 스레드가 결과를 대기 할수 있습니다.
//  std::thread t1(&f1, sf2); // 값으로 보내도 되고 참조로 보내도 됩니다.
//  std::thread t2(&f2, sf3);

    
    // 핵심 4. future 에서 shared_future를 꺼낸 경우는
    // 주스레드도 반드시 shared_futre로 대기해야 합니다.
    // 만약, 아래처럼 "future"로 대기하면 
    // => shared_future 를 사용해서 get()하는 모든 코드는 예외 입니다.
//  int ret1 = ft.get();    // shared_future를 꺼내지 않은 경우만 사용


    int ret1 = sf1.get();  // shared_future를 꺼낸 경우.

    t.join();
}




