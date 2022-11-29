#include <iostream>
#include <thread>
#include <string_view>

// 73 page

// 3의 배수를 차례대로 반환 하는 함수를 생각해 봅시다.(3, 6, 9)
int next3times()
{
//	int n = 0;			// 지역변수, stack 사용, 함수 호출이 종료되면 파괴!

	static int n = 0;	// static 지역변수, static(data) 메모리사용, 
						// 함수 호출이 종료되어도 파괴 안됨.
	n = n + 3;
	return n;
}

void foo(const std::string& name)
{
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
	std::cout << name << " : " << next3times() << std::endl;
}

int main()
{
	foo("A");
}



