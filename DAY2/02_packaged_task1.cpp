#include <iostream>
#include <thread>
#include <future>

// 39 page

// add 함수가 promise 를 통해서 반환값 전달
// 다른 스레드에 반환
// => 즉, add 함수를 만들때 스레드를 고려 해서 설계했다는 의미!!!
// => 스레드를 고려하지 않았다면 "return 값" 으로 결과를 반환!
void add(std::promise<int>& p, int a, int b)
{
	p.set_value(a + b);
}

int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();

	std::thread t(add, std::ref(pm), 10, 20);

	int ret = ft.get();

	t.join();
}



