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

	// �̱۽�����!
	// for_each(v.begin(), v.end(), foo);
	
	// C++17 ���� 69������ �˰����� ���� ������ �����˴ϴ�.
	// => �츮�� ���� "parallel_sum" ó�� �Ǿ� �ֽ��ϴ�.
	for_each( std::execution::par,   v.begin(), v.end(), foo);


	// ���� ! �Ʒ� ó�� ����Ѵٸ� "s" �� ����ȭ �ʿ��մϴ�.(���� ����)
	// 
//	int s = 0;
//	for_each(std::execution::par, v.begin(), v.end(), 
//		[&s](int a) { s += a; });
}





// ����Ȯ���� command line ���� �غ��� ���� �����ϴ�.
// g++ �ҽ�.cpp -std=c++20  
// cl  �ҽ�.cpp /std:c++latest