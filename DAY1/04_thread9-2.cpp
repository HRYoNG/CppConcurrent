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
    //===============================================================
    // cnt_thread : 생성할 스레드 갯수
    // cnt_element: vector에 있는 요소의 갯수

    const std::size_t block_size = cnt_element / cnt_thread;

    // 스레드가 10개 필요하다면
    // => 9개 스레드 객체만 만들면 됩니다. 1개는 주스레드
    // => 각각 스레드의 결과는 담을 vector 는 10개 크기 필요
    std::vector<RT> result_vector(cnt_thread); // 현재 RT는 int 입니다.
    std::vector<std::thread> thread_vector(cnt_thread-1);

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

    return 0;
}










int main()
{
    init();

    auto s = parallel_sum(v.begin(), v.end(), 0); // 0은 초기값


    std::cout << s << std::endl;
}
