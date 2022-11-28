#include <iostream>
#include <chrono>

int main()
{
	// 변환 이야기 
	std::chrono::seconds s(70); // 70 초

	std::cout << s.count() << std::endl; // 70


	// "nano 초 = 초"는 데이타 손실이 없습니다.
	// 아래와 같이 그냥 복사(대입) 됩니다.
	std::chrono::nanoseconds n = s;

	std::cout << n.count() << std::endl; // 70000000000 


	// "분 = 초" 는 데이타 손실이 있습니다.
	// 명시적 캐스팅이 필요 합니다.
	// std::chrono::minutes m = s;	// error

	std::chrono::minutes m =
		std::chrono::duration_cast<std::chrono::minutes>(s);


	std::cout << m.count() << std::endl; // 1

//	using namespace std::chrono; // 이렇게 하면 namespace 이름
								// 없이 사용가능하지만
								// 요즘은 권장하지 않습니다.
								// 이름 충돌 발생
}
