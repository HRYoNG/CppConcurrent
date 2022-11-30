#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// promise & future 모델
// => 자식 스레드가 수행한 연산의 결과를 얻기 위해 사용
// => 한번만 사용가능.

// 한번만 사용하지 말고, 계속 신호를 주고 받으면서 
// 범용적인 용도로 사용할수 없을까 ?

// => "std::condition_variable" 
// => 가장 중요한 동기화 도구!!
// => 사용법이 약간 까다롭게.. 


void add(std::promise<int>& pro, int a, int b)
{
	std::this_thread::sleep_for(2s);

	int result = a + b;

	pro.set_value(result);	// 스레드가 결과를 알리고 싶을때.. 
}


int main()
{
	std::promise<int> pro;
	std::future<int> ft = pro.get_future();

	std::thread t(add, std::ref(pro), 10, 20);

	int result = ft.get();	// pro.set_value()를 할때 까지 대기 합니다.

	std::cout << "스레드함수의 결과 : " << result << std::endl;

	t.join();

}

