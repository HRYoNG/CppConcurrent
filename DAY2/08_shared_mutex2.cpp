#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex> // C++17
#include <string_view>
using namespace std::literals;


// 1. 쓰는 동안, 다른 스레드는 읽을수 없어야 한다.
// 2. 쓰는 동안, 다른 스레드는 쓸수 없어야 한다.
// 3. 읽는 동안, 다른 스레드는 쓸수 없어야 한다.
// 
// 4. 읽는 동안, 다른 스레드도 읽을수 있어야 한다. <<=== 핵심 !!







//std::mutex m;

std::shared_mutex m;

int share_data = 0;


void Writer()
{
    while (1)
    {
        m.lock();
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}


void Reader(const std::string& name)
{
    while (1)
    {
        m.lock_shared();
        
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);
        m.unlock_shared();

        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    std::thread t1(Writer);
    std::thread t2(Reader, "A");
    std::thread t3(Reader, "B");
    std::thread t4(Reader, "C");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}



