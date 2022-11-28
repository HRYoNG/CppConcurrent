#include <iostream>
#include <chrono>
using namespace std::literals; // 30s, 3min, 3ns, 3ms 등을사용하기위해

void foo(std::chrono::seconds sec) {}

int main()
{
	// 30초를 나타내는 객체를 만드는 2가지 방법

	// 방법 1. 타입의 이름을 직접 사용
	std::chrono::seconds s1(30);

	// 방법 2. "user define literals" 문법으로 만들어진 접미사 사용
	auto s2 = 30s; // std::chrono::seconds operator""s(30) 이라는 함수가 호출됩니다.
}
