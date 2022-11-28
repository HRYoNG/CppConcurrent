#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include "chronometry.h"
constexpr std::size_t sz = 10000000;

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
    auto cnt_element = std::distance(first, last);

    if (cnt_element == 0) return 0;

    std::size_t hw_cnt_thread = std::thread::hardware_concurrency();

    if (hw_cnt_thread == 0)
        hw_cnt_thread = 2;

    const std::size_t min_per_thread = 25;

    const std::size_t max_cnt_thread =
        (cnt_element + min_per_thread - 1) / min_per_thread;

    const std::size_t cnt_thread =
        std::min(hw_cnt_thread, max_cnt_thread);

    std::cout << "생성할 스레드 갯수 : " << cnt_thread << std::endl;

    const std::size_t block_size = cnt_element / cnt_thread;

    std::vector<RT> result_vector(cnt_thread); // 현재 RT는 int 입니다.
    std::vector<std::thread> thread_vector(cnt_thread - 1);

    IT block_start = first;

    for (int i = 0; i < cnt_thread - 1; i++)
    {
        IT block_end = block_start;
        std::advance(block_end, block_size);

        thread_vector[i] = std::thread(sum<IT, RT>,
            block_start, block_end,
            std::ref(result_vector[i]));

        block_start = block_end;
    }

    sum(block_start, last, result_vector[cnt_thread - 1]);

    for_each(thread_vector.begin(), thread_vector.end(),
        [](auto& t) { t.join(); });

    return std::accumulate(result_vector.begin(),
        result_vector.end(), init);
}


int f1()
{
    int s = 0;
    sum(v.begin(), v.end(), s);    // 싱글 스레드 알고리즘
    return s;
}
int f2()
{
    auto s = parallel_sum(v.begin(), v.end(), 0); // 병렬 알고리즘
    return s;
}
int main()
{
    init();
    
    chronometry(f1);
    chronometry(f2);

}
