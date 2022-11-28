#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std::literals;

void foo(int n)
{
	std::cout << std::this_thread::get_id() << " : " << n << std::endl;
	
	std::this_thread::sleep_for(10ms);
}

int main()
{
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,0 };

	for_each(v.begin(), v.end(), foo);
}