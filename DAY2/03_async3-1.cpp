// async1 - packaged task2 복사
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;



int add(int a, int b)
{
	std::cout << "add" << std::endl;
	std::this_thread::sleep_for(2s);
	std::cout << "finish add" << std::endl;
	return a + b;
}

int main()
{
	// 핵심 : async 의 반환값(future)를 받지 않을때 나타나는 현상
	// => 마치, 스레드 생성이 아닌, 일반 호출 처럼 동작합니다.
	// => add 함수가 종료되어야 "main 이 계속 실행" 됩니다.
	// 이유 : async 가 반환하는 것은 임시객체인데, 
	//       임시객체는 해당 문장의 끝에서 파괴 됩니다.
	//       이때 임시객체인 future 의 소멸자에서 대기(get호출)하게됩니다.
	std::async(add, 10, 20);

	std::cout << "main 계속 실행" << std::endl;
}	
/*
// async 는 future 를 값 타입으로 반환 합니다.
// 임시객체가 반환 됩니다.
std::future<int> async(...)
{
	std::future<int> ret = ....;
	return ret;
}
*/
