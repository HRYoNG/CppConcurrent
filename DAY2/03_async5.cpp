#include <chrono>
#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <string>
#include <numeric>
#include <execution>
#include "chronometry.h"

static const int NUM = 1000000; 

std::vector<int> v1, v2;

// v1, v2 를 "NUM" 만큼의 난수를 채우는 함수.
void fill_vector()
{
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> dist(0, 100);

    v1.reserve(NUM);
    v2.reserve(NUM);

    for (int i = 0; i < NUM; ++i)
    {
        v1.push_back(dist(engine));
        v2.push_back(dist(engine));
    }
}
//=========================================================

// vector 내적 구하기
long long f1()
{
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0LL);
}

long long f2()
{
    // 4개의 스레드를 사용해서 내적 구하기
    long long block_size = NUM / 4;
    
    auto v1_first = v1.begin();
    auto v1_last = std::next(v1_first, block_size);
    
    auto v2_first = v2.begin();

    
    // async 장점 : 기존 함수의 반환값을 그대로 받을수 있다는 점.
    //             std::thread 사용시는 std::ref()로 값을 담을 변수를
    //              전달했어야 합니다. - 1일차 예제

    std::future<long long> ft1 = std::async([v1_first, v1_last, v2_first]
                            { return std::inner_product(v1_first, v1_last, 
                                                        v2_first, 0LL); });
    // 위 람다가 반복자를 값 캡쳐 했으므로 주스레드는 
    // 아래 반복자를 변경해도 동기화 문제 없습니다.
    std::advance(v1_first, block_size);
    std::advance(v1_last , block_size);
    std::advance(v2_first, block_size);

    std::future<long long> ft2 = std::async([v1_first, v1_last, v2_first]
        { return std::inner_product(v1_first, v1_last,
            v2_first, 0LL); });

    std::advance(v1_first, block_size);
    std::advance(v1_last, block_size);
    std::advance(v2_first, block_size);

    std::future<long long> ft3 = std::async([v1_first, v1_last, v2_first]
        { return std::inner_product(v1_first, v1_last,
            v2_first, 0LL); });

    std::advance(v1_first, block_size);
    v1_last = v1.end();
    std::advance(v2_first, block_size);

    std::future<long long> ft4 = std::async([v1_first, v1_last, v2_first]
        { return std::inner_product(v1_first, v1_last,
            v2_first, 0LL); });

    return ft1.get() + ft2.get() + ft3.get() + ft4.get();
}

int main()
{
    fill_vector();
    
    chronometry(f1);
    chronometry(f2);
}