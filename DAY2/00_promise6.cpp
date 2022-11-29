#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>


int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

    // 작업 1. v1의 부분합을 구해서 v2에 넣기
    std::partial_sum(v1.begin(), v1.end(), v2.begin());


    //=============================================
    // 스레드를 생성해서. "작업3"을 수행하도록합니다.
    // => "작업3"을 일반함수가 아닌 람다 표현식으로 수행합니다.
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    // promise5번예제 : 별도의 함수(work)를 만들어서 스레드로 수행
    // promise6번예제 : 일반 함수가 아닌 람다표현식으로 스레드로 수행
    std::thread t([&p, &v2]() {

        int s = std::accumulate(v2.begin(), v2.end(), 0);
        p.set_value(s);

        } );








    //============================================
    // 작업 2. v2 의 모든 요소를 화면 출력
    for (auto n : v2)
        std::cout << n << ", ";

    // 스레드가 수행하는 작업3의 결과를 대기합니다.
    int s = ft.get();

    std::cout << "\n" << s << std::endl;

    t.join();
}

