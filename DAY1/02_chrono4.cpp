#include <iostream>
#include <chrono>
#include <string>

int main()
{
    // 1. 현재 시간을 얻는 방법
    //    "std::chrono::system_clock" 클래스의 정적 멤버 함수 "now"사용
    
    // time_point : 기준시간으로 부터 "얼마나 경과" 했는가..

    std::chrono::system_clock::time_point tp =
                                std::chrono::system_clock::now();

    // epoch_time : 기준 시간을 1970년 1월 1일 정오 를 기준으로 하는 시간
    std::chrono::nanoseconds ns = tp.time_since_epoch();
    
    std::chrono::seconds ss = 
        std::chrono::duration_cast<std::chrono::seconds>(ns);


    std::chrono::hours hh = 
        std::chrono::duration_cast<std::chrono::hours>(ns);

    std::cout << ns.count() << std::endl;
    std::cout << ss.count() << std::endl;
    std::cout << hh.count() << std::endl;
}