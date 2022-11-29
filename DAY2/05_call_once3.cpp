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

    // meyer's �̱���
    // => ���� �Ѱ��� ��ü�� static ���������� ����� ���.!
    // => effective-c++ �� ������ "scott-meyer" �� ó�� ���� ���

    // => C++11 ���� static ���������� ������ ȣ���� ��Ƽ�����忡
    //    �����ϰ� �����մϴ�.


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



