#include <iostream>
#include <thread>

void foo() {}

int main()
{
//  std::thread t1(&foo);   // 스레드 생성됨
//  t1.join(); // ok.. 


    std::thread t2; // 함수를 전달하지 않았습니다.
                    // 스레드 생성되지 않습니다

    t2.join();  // 예외 발생!



}
