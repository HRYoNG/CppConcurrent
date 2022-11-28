#include <iostream>
#include <string>
#include <thread>

// OS가 제공하는 스레드 생성함수를 사용하면
// => 스레드가 수행하는 함수 모양에 제약이 있습니다.(인자 void* 한개)

// C++ thread : 스레드가 수행하는 함수 모양에는 제약이 없습니다.
void f1() { }
void f2(int a, double d) { }
void f3(int a, int& b, std::string&& s) { b = 100; }

int main()
{
    int n = 0;
    std::string s = "hello";

    // 인자 전달 방법
    std::thread t1( &f1 );
    std::thread t2( &f2, 1, 3.4);

    // 핵심 : 인자를 참조로 전달할때는 "std::ref()" 를 사용합니다.
    // => 단, 지역변수를 다른 스레드의 참조로 전달하는 것은 아주 위험합니다.
    std::thread t3( &f3, 1, std::ref(n), std::move(s) );

    t1.join();
    t2.join();
    t3.join();
}

