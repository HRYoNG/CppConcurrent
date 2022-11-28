#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

// 핵심 : jthread에 전달되는 스레드 함수의 모양
// 1. f( 인자들 )
// 2. f( std::stop_token, 인자들 )

void foo( std::stop_token quit_token )
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

        if (quit_token.stop_requested())
            break;
    }
    std::cout << "finish foo" << std::endl;
}

void goo()
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "goo : " << i << std::endl;
    }
}
int main()
{
    std::jthread j1(&foo);  // 핵심 - foo 함수에 어떠한 인자도 보내지
                            //       않고 있습니다.
    std::jthread j2(&goo);

    std::this_thread::sleep_for(2s);

    j1.request_stop(); // 중지해 달라고 요청
    j2.request_stop(); // 중지해 달라고 요청 했지만 처리 하는 코드가 없다.
                        // 에러는 아니고, 아무효과도 없다.
}
// 결국 C++20 의 jthread 는
// 1. 소멸자에서 자동 join() 기능
// 2. 협력적 취소 모델이 추가된 것