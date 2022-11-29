#include <iostream>
#include <thread>
#include <future>

// 스레드를 고려하지 않고 만들어진 일반 함수는 대부분
// "return 값" 으로 결과를 전달합니다.
int add(int a, int b)
{
	std::cout << "add" << std::endl;

	return a + b;
}

int main()
{
	// packaged_task : "return 값" 으로 결과를 반환하는 함수를
	//				   스레드로 실행하고 결과를 얻는 도구.

	// 1. packaged_task 의 객체를 만들고 future 객체를 꺼내세요
	std::packaged_task<int(int, int)> task(add);

	std::future<int> ft = task.get_future();

	// 2. packaged_task 의 타입의 객체인 "task" 는 ()연산자가 재정의
	// 되어 있습니다.
	// task(10, 20); // add(10,20) 이 실행됩니다.
				  // 단, 이코드는 스레드로 실행하는 것은 아닙니다.
				  // 또한, 결과는 future를 통해서 꺼내야 합니다.

	// 3. task 를 스레드로 실행하면 됩니다.
	// => task 전달시 "std::ref()" 또는 "std::move()" 가능합니다.
	// std::ref(task)  : task 객체를 계속 사용하고 싶을때
	// std::move(task) : task 객체를 더 이상 사용할수 없습니다.
	//					=> 한번만 사용한다면 move 로 하세요
	std::thread t(std::move(task), 10, 20);

	int ret = ft.get();

	std::cout << ret << std::endl;

	t.join();

	// 참고
//	std::thread t1(add, 10, 20); // add의 결과를 받을 방법이 없습니다
								 // promise 사용해야 합니다.
								 // => add 함수 모양 변경해야 합니다.

//	std::thread t2(std::ref(task), 10, 20);
								// add 함수의 모양을 변경하지 않고도
								// 결과를 반환 받을수 있습니다.
								// future 사용
}

