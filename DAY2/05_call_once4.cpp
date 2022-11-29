#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Object
{
    int member_data;
public:
    Object()
    {
        std::cout << "start ctor" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish ctor" << std::endl;
    }
    void init()
    {
        std::cout << "start init" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish init" << std::endl;
    }
};

void foo()
{
    // 핵심 1. 지역변수 - 스레드 별로 따로 생성됩니다.
    // => 스레드당 따로 객체가 생성
    // => 생성자도 각각 호출
    // => 데이타를 따로 사용하므로 동시에 실행되어도 안전
    Object obj1;


    // 핵심 2. static 지역변수, 
    // => 스레드가 여러개 수행되어도 객체는 한개
    // => 생성자 호출은 동기화 됨.
    // => 최초 도착한 스레드만 생성자 호출. 이후 도착한 스레드는 대기.
    static Object obj2;


    // 핵심 3. 일반 멤버 함수 호출은 동기화 되지 않습니다.
    // => 스레드가 각각 아래 init 호출
    // => 동기화 필요 하거나, 한번만 호출되게 하려면 call_once 사용.
    obj2.init();


    // 핵심 4. 객체를 동적으로 생성
    // => 역시, 스레드 별로 따로 객체 생성
    // => 생성자도 동시에 실행
    Object* p = new Object;
    delete p;
}



int main()
{
    std::thread t1(&foo);
    std::thread t2(&foo);

    t1.join();
    t2.join();
}



