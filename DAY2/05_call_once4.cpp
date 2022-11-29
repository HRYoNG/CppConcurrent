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
    // 지역변수 - 스레드 별로 따로 생성됩니다.
    Object obj1;

    static Object obj2;

    obj2.init();


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



