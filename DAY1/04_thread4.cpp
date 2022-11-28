#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// 스레드 ID

void foo()
{
    // 현재 함수를 실행하는 자신의 스레드 ID 얻기
    std::cout << std::this_thread::get_id() << std::endl;
}
int main()
{
    std::thread t(&foo);
    
    std::this_thread::sleep_for(1s);

    // 자신이 생성한 스레드의 ID 얻기 
    std::thread::id tid = t.get_id();
    
    std::cout << "created thread id : " << tid << std::endl;

    t.join();
}

