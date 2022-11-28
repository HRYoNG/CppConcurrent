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

    // 마지막 구간은 주스레드가 연산하면 됩니다.
    // => 주스레드가 수행하므로 "std::ref()" 필요 없습니다.
    sum(block_start, last, result_vector[cnt_thread - 1] );

    // 모든 스레드의 종료를 대기 합니다.
    for_each(thread_vector.begin(), thread_vector.end(),
                        [](auto& t) { t.join(); });

    // result_vector 안의 모든 결과를 더하면 됩니다.
    return std::accumulate( result_vector.begin(), 
                            result_vector.end(), init);
}

int main()
{
    init();
    auto s = parallel_sum(v.begin(), v.end(), 0); // 0은 초기값
    std::cout << s << std::endl;


}
/*
// 결과를 반환하는 방법
// => 여러개의 스레드로 각각의 구간을 나누어 결과를 담기에는 2번 방법이 편리합니다.
int sum() {}            // 1. 리턴값으로 반환
void sum(int& ret) {}   // 2. 마지막 인자에 담아 오는 방법
                  
// 스레드가 수행하면 std::ref() 가 필요없는 이유가 뭔가요 ? ?
int n = 0;
sum(n); // 주 스레드는 그냥 이렇게 하세요

std::thread t(&sum, std::ref(n)); // n을 직접 보내지 않고
                                // thread 생성자를 거치게 됩니다.
                                */