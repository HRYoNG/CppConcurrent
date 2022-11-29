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

    // 작업 2. v2 의 모든 요소를 화면 출력
    for (auto n : v2)
        std::cout << n << ", ";

    // 작업 3. v2의 모든 요소의 합을 구하기
    int s = std::accumulate(v2.begin(), v2.end(), 0);
    
    // 작업 4. 결과 출력
    std::cout << "\n" << s << std::endl;
}



