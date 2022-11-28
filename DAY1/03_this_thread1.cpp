#include <iostream>
#include <thread>   // C++11 부터 지원 되는 헤더
#include <vector>
#include <unordered_set>

// std::this_thread 라는 namespace 안에 4개의 도움 함수가 있습니다.

int main()
{
    // 1. get_id()로 스레드 ID 얻기. 
    std::cout << std::this_thread::get_id() << std::endl;


    std::thread::id tid1 = std::this_thread::get_id();
    // class thread
    // {
    //      using id = 구현에 따라 다른데 보통 "struct thread_id{}"
    // } 

    // 스레드 id 특징
    // 1. int 변환 안됩니다.
    int n1 = tid1;  // error

    // 2. container 에 저장 가능하고, 
    //    hash 가능하므로 unordered_set 에 담을수있습니다
    std::vector<std::thread::id> v;
    std::hash<std::thread::id> h;
    std::unordered_set<std::thread::id> s;

    // 3. 상등연산(==, !=) 가능합니다.
    auto t1 = std::this_thread::get_id();
    auto t2 = std::this_thread::get_id();

    bool b1 = t1 == t2;
    bool b1 = t1 != t2;
}
// 핵심 : 스레드 ID 를 정수 라고 생각하지는 마세요
//       "std::thread::id" 타입 입니다.
