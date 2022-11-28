#include <thread>

void foo() {}
void goo() {}

void f1(std::thread t) {   t.join();}

std::thread f2()       { return std::thread(&foo);}

int main()
{
    // 핵심 1. 함수 인자로 스레드 객체 전달하기
    std::thread t1(&foo);

//  f1(t1);             // error. copy 될수 없다.
    f1(std::move(t1));  // ok
    f1(std::thread(&foo)); // ok. 임시객체는 rvalue!

    // 핵심 2. std::thread 를 반환하는 함수
    std::thread t2 = f2(); // ok
                // => 1. f2() 는 값 반환 입니다.
                // => 2. 임시객체로 반환 됩니다.
                // => 3. 임시객체는 rvalue 이고 move 생성자 호출
    t2.join();

}



