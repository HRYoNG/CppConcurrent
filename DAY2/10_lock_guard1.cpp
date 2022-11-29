#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// 핵심 : 자원을 사용후, 함수의 마지막 줄에서 직접 반납하는 코드는 사용하지 마세요
void f()
{
    // 자원 획득...

    // 자원 사용

    // 자원 반납.. <<==== 절대 이렇게 하지 마세요
}

// 해결책 : 생성자/소멸자로 자원을 관리 하세요..


std::mutex m;

void goo()
{
    m.lock();    
    std::cout << "using shared data" << std::endl;

    throw std::exception(); // 예외 발생

    m.unlock();
}

void foo()
{
    try
    {
        goo();
    }
    catch (...)
    {
        std::cout << "발생된 예외 처리 완료" << std::endl;
    }
}



int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



