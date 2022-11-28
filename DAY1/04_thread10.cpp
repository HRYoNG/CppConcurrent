#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>
#include <execution>
#include <vector>
using namespace std::literals;

void foo(int n)
{
	std::cout << std::this_thread::get_id() << " : " << n << std::endl;
	
	std::this_thread::sleep_for(5s);
}

int main()
{
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,0 };

	// 싱글스레드!
	// for_each(v.begin(), v.end(), foo);
	
	// C++17 부터 69여개의 알고리즘의 병렬 버전이 지원됩니다.
	// => 우리가 만든 "parallel_sum" 처럼 되어 있습니다.
	for_each( std::execution::par,   v.begin(), v.end(), foo);


	// 주의 ! 아래 처럼 사용한다면 "s" 는 동기화 필요합니다.(내일 주제)
	// 
//	int s = 0;
//	for_each(std::execution::par, v.begin(), v.end(), 
//		[&s](int a) { s += a; });
}





// 성능확인은 command line 에서 해보는 것이 좋습니다.
// g++ 소스.cpp -std=c++20  
// cl  소스.cpp /std:c++latest