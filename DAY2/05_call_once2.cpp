#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton() = default;
    static Singleton* sinstance;
    
    static std::once_flag flag;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance()
    {
        std::call_once(flag, init);
        return sinstance;
    }
    static void init()
    {
        std::cout << "init" << std::endl;
        sinstance = new Singleton;
        
    }
};
Singleton* Singleton::sinstance = nullptr;
std::once_flag Singleton::flag;

void foo()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;

    std::thread t1(&foo);
    std::thread t2(&foo);

    t1.join();
    t2.join();  
}



