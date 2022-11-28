#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

void foo(bool& flag)
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

        // 새로운 스레드는 주기적으로 cancel flag 를 확인합니다.
        if (flag == true)
            break;
    }
    // 사용하던 자원들을 release 하고  종료 합니다.

    std::cout << "finish foo" << std::endl;

    return;
}

int main()
{
    bool quit = false;

    std::thread t(foo, std::ref(quit));

    std::this_thread::sleep_for(2s);

    quit = true;    // 생성했던 스레드 종료!!

    t.join();
}