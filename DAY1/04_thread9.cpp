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

int main()
{
    init();
    int s = 0;    

//  sum( v.begin(), v.end(), s);    // 주스레드가 실행


//  std::thread t(sum, v.begin(), v.end(), std::ref(s)); // error
                        // => 왜 에러일까요 ?
                        // => sum 이 템플릿 인데, 직접 호출이 아니므로
                        // => IT와 RT 타입의 추론이 안됩니다.

    std::thread t(sum<std::vector<int>::iterator, int>, 
                  v.begin(), v.end(), std::ref(s));

    t.join();


    std::cout << s << std::endl;
}
