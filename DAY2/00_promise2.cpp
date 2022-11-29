#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 일반함수 : 함수 반환값으로 결과를 반환
int add1(int a, int b)
{
	int s = a + b;
	return s;
}

// out parameter 로 값을 반환하는 경우.
void add2(int a, int b, int& s)
{
	s = a + b;
}

//==============================================
void add3(int a, int b, std::promise<int>& pr)
{
	int s = a + b;
	std::this_thread::sleep_for(3s); // 연산시간이 3초 걸린다고 가정

	// 연산이 완료되면 promise 객체의 set_value로 전달합니다.
	pr.set_value(s); 

	std::this_thread::sleep_for(3s); // 마무리 작업에 3초 정도 소요!!
}


int main()
{
	// 1. promise 객체 생성.
	std::promise<int> pr;

	// 2. promise 안에 있는 future 객체를 꺼냅니다.
	std::future<int> ft = pr.get_future();

	// 3. 스레드 생성시 promise 객체를 참조로 전달하세요
	// => std::ref() 또는 std::move() 로 전달
	std::thread t(add3, 10, 20, std::ref(pr));

	// 다른 작업을 하다가
	std::cout << "main 함수 계속 실행" << std::endl;

	// 4. 스레드의 결과가 필요하면 future객체에서 꺼내세요
	int ret = ft.get(); // 이순간
						// 1. 결과가 들어 있으면 바로 꺼내고
						// 2. 결과가 아직 없으면 대기하게 됩니다.
					 	//    스레드가 "pr.set_value()" 할때 까지 대기
	// 결과 사용!!
	std::cout << "스레드 수행 결과 : " << ret <<  std::endl;


	t.join();
}



