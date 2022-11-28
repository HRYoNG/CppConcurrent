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


// ������ ���� ���ϴ� �Լ�.
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

    std::cout << "������ ������ ���� : " << cnt_thread << std::endl;
    //===============================================================
    // cnt_thread : ������ ������ ����
    // cnt_element: vector�� �ִ� ����� ����

    const std::size_t block_size = cnt_element / cnt_thread;

    // �����尡 10�� �ʿ��ϴٸ�
    // => 9�� ������ ��ü�� ����� �˴ϴ�. 1���� �ֽ�����
    // => ���� �������� ����� ���� vector �� 10�� ũ�� �ʿ�
    std::vector<RT> result_vector(cnt_thread); // ���� RT�� int �Դϴ�.
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

    auto s = parallel_sum(v.begin(), v.end(), 0); // 0�� �ʱⰪ


    std::cout << s << std::endl;
}
