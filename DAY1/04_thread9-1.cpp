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
    // 1. ����� ���� ���ϱ�
//  auto cnt_element = last - first; // �������� �ݺ��ڸ� ����
    auto cnt_element = std::distance(first, last);

    if (cnt_element == 0) return 0;

    // 2. ���� �ϵ����� ���ÿ� ���డ���� ������ ���� ���ϱ�
    std::size_t hw_cnt_thread = std::thread::hardware_concurrency();

    if (hw_cnt_thread == 0)
        hw_cnt_thread = 2;

    // 3. ������ ���� ���ϱ� (�ٽ� �ڵ�!! )
    const std::size_t min_per_thread = 25; // �Ѱ� �����尡 ó�����ּҰ���
    
    const std::size_t max_cnt_thread =
            (cnt_element + min_per_thread - 1) / min_per_thread;

    const std::size_t cnt_thread = 
                    std::min(hw_cnt_thread, max_cnt_thread);


    std::cout << "������ ������ ���� : " << cnt_thread << std::endl;

    return 0;
}







int main()
{
    init();

    auto s = parallel_sum(v.begin(), v.end(), 0); // 0�� �ʱⰪ
    

    std::cout << s << std::endl;
}
