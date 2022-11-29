#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton()
    {
        std::cout << "start ctor" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish ctor" << std::endl;
    }
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // meyer's 싱글톤
    // => 오직 한개의 객체를 static 지역변수로 만드는 기술.!
    // => effective-c++ 의 저자인 "scott-meyer" 가 처음 만든 기술

    // => C++11 부터 static 지역변수의 생성자 호출은 멀티스레드에
    //    안전하게 동작합니다.


    static Singleton& getInstance()
    {
        std::cout << "start getInstance" << std::endl;
    
        static Singleton instance;
        
        std::cout << "finish getInstance" << std::endl;

        return instance;
    }
};




void foo()
{
    Singleton& s = Singleton::getInstance();
    std::cout << &s << std::endl;
}
int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
}



