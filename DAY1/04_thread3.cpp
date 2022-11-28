#include <iostream>
#include <thread>

// 스레드 함수의 모양
// 1. foo 는 일반함수
void foo(int a, double d) {}

// 2. Run 은 멤버 함수
struct Machine
{
    void Run(int a, double d) {}
};

// 3. ()연산자를 재정의한 함수 객체
struct Work
{
    void operator()(int a, double b) const {}
};

int main()
{
    // 1. 일반 함수
    std::thread t1(&foo, 1, 3.4); // 일반 함수를 스레드로

    // 2. 멤버 함수
    Machine m;
    std::thread t2(&Machine::Run, &m, 1, 3.4);
                    // => m.Run(1, 3.4) 를 스레드로 실행

    // 3. 함수 객체
    Work w;
    w(1, 3.4); // () 연산자가 재정의 되어서 함수 처럼 사용가능
    std::thread t3(w, 1, 3.4);
//  std::thread t3(&w, 1, 3.4);// 주의!! error
                            // => w(1, 3.4) 는 되지만
                            // => (&w)(1, 3.4) 는 에러

    // 4. 람다 표현식
    std::thread t4([]() {std::cout << "lambda" << std::endl; });

    // 결론 : 호출가능한 모든 것(callable object)를
    //        스레드로 실행가능.

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

