#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
    // 핵심 1. thread 생성하면 반드시 join() 또는 detach()해야 합니다.
    std::thread t1(&do_work, 1);
    t1.join();

    //==========================================
    // 핵심 2. vector 로 10개의 스레드 관리하기

    std::vector<std::thread> v; // 크기가 0인 vector

    for (int i = 0; i < 10; i++)
    {
        // 방법 1.
        std::thread t(&do_work, 3);
        v.push_back(t);


    }


}
