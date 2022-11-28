#include <iostream>
#include <thread>

void foo() {}

int main()
{
//  std::thread t1(&foo);   // 스레드 생성됨
//  t1.join(); // ok.. 


    std::thread t2; // 함수를 전달하지 않았습니다.
                    // 스레드 생성되지 않습니다

    try
    {
        t2.join();  // 예외 발생!
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    // 위처럼 예외 처리하거나
    // 아래 처럼 사전 조사 하세요!
    if (t2.joinable())
        t2.join();

    // 1. 스레드를 생성하지 않았거나 
    // 2. detach()로 분리했거나
    // 3. 이미 join() 을 했거나!!
    // 1~3의 경우에 다시 .join()하면 예외 입니다.
}
