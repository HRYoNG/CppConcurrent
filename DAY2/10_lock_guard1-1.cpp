#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// 해결책 : 생성자/소멸자로 자원을 관리 하세요..


std::mutex m;

void goo()
{
//    m.lock();

    std::lock_guard<std::mutex> g(m); // 생성자에서 m.lock()합니다.

    std::cout << "using shared data" << std::endl;

    throw std::exception(); // 예외 발생
                // stack unwiniding(스택 풀기)
                // => 예외 발생시 지역변수는 안전하게 파괴 되고 catch 로 이동
                // => 즉, g의 소멸자가 호출되고 catch로 이동.

//    m.unlock();

}   // <= g 가 파괴되는데, 소멸자에서 unlock() 합니다.



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



