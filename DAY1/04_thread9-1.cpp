#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

constexpr std::size_t sz = 1'000'000;

std::vector<int> v;

void init()
{
    for (int i = 0; i < sz; ++i)
    {
        v.push_back(i);
    }
}


// 구간의 합을 구하는 함수.
template<typename IT, typename RT>
void sum(IT first, IT last, RT& result)
{
    result = std::accumulate(first, last, result);
}

template<typename IT, typename RT>
RT parallel_sum(IT first, IT last, RT init)
{
    // 1. 요소의 갯수 구하기
//  auto cnt_element = last - first; // 임의접근 반복자만 가능
    auto cnt_element = std::distance(first, last);

    if (cnt_element == 0) return 0;

    // 2. 현재 하드웨어에서 동시에 실행가능한 스레드 갯수 구하기
    std::size_t hw_cnt_thread = std::thread::hardware_concurrency();

    if (hw_cnt_thread == 0)
        hw_cnt_thread = 2;

    // 3. 스레드 갯수 구하기 (핵심 코드!! )
    const std::size_t min_per_thread = 25; // 한개 스레드가 처리할최소갯수
    
    const std::size_t max_cnt_thread =
            (cnt_element + min_per_thread - 1) / min_per_thread;

    const std::size_t cnt_thread = 
                    std::min(hw_cnt_thread, max_cnt_thread);


    std::cout << "생성할 스레드 갯수 : " << cnt_thread << std::endl;

    return 0;
}







int main()
{
    init();

    auto s = parallel_sum(v.begin(), v.end(), 0); // 0은 초기값
    

    std::cout << s << std::endl;
}
