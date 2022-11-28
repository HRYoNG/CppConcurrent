#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

     
void foo()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "foo : " << i << std::endl;
        std::this_thread::sleep_for(100ms);
    }
}

int main()
{
//  foo();  // 주스레드가 그냥 실행!!

    // 핵심 1. 스레드를 생성하는 방법.
    std::thread t1(&foo);   // 이순간 새로운 스레드가 생성되어서
                            // foo 실행.
                            // 별도의 "start()"같은 함수 없습니다.
                            // 객체만 생성하면 됩니다.

    // 핵심 2. 스레드를 생성한 경우 반드시 "대기" 하거나 "분리" 해야 합니다.
    // t1.join();  // 새롭게 생성된 스레드가 종료 할때 까지 주스레드 대기
                // linux   : pthread_join()
                // windows : WaitForSingleObject()

    t1.detach();    // 스레드 분리 하기
                    // => 새로운 스레드를 만들면 주스레드가 새로운 스레드의
                    //    핸들을 가지고 있는데, 핸들을 닫는 작업.

    std::cout << "main 함수(주스레드) 종료" << std::endl;
}
// C++ 스레드에서
// => 주스레드의 종료는 process의 종료 입니다.
// => 즉, 주스레드가 종료되면 활동중인 모든 스레드는 강제 종료 됩니다
// => "강제 종료" 는 좋은 현상은 아닙니다.!!

// 참고 C#언어는
// foreground thread : 주스레드 종료되어도 계속 실행가능
// background thread : 주스레드 종료되면 스레드도 강제 종료