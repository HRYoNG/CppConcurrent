#include <iostream>
#include <chrono>

// chrono 라이브러리 : 시간관련 라이브러리(C++11)
// 14 page

int main()
{
	// 핵심 1. 시간 관련 타입 알아두세요..
//	std::chrono::seconds s1 = 30;	// error. explicit 생성자
	std::chrono::seconds s2(30);	// ok

	std::chrono::nanoseconds ns(1);
	std::chrono::microseconds us(1);
	std::chrono::milliseconds ms(1);
	std::chrono::seconds ss(1);
	std::chrono::minutes m(1);
	std::chrono::hours   h(1);

	// C++20 에는 days, months, years 타입도 추가되었습니다.
	

}
