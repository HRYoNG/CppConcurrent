#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

// 작업3을 수행할 스레드 함수
void work(std::promise<int>& p, std::vector<int>& v)
{
    int s = std::accumulate(v.begin(), v.end(), 0);

    p.set_value(s);
}


int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

    // 작업 1. v1의 부분합을 구해서 v2에 넣기
    std::partial_sum(v1.begin(), v1.end(), v2.begin());

    //=============================================
    // 스레드를 생성해서. "작업3"을 수행하도록합니다.
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    std::thread t(work, std::ref(p), std::ref(v2) );


    //============================================
    // 작업 2. v2 의 모든 요소를 화면 출력
    for (auto n : v2)
        std::cout << n << ", ";

    // 스레드가 수행하는 작업3의 결과를 대기합니다.
    int s = ft.get();

    std::cout << "\n" << s << std::endl;

    t.join();
}

// 작업1 이 종료되어야만 작업2, 작업3을 할수 있습니다.
// 작업2와 작업3은 독립된 작업입니다.
// => 시간이 오래 걸리는 작업이면 2개중에 한개를 스레드로 수행해도 됩니다.


