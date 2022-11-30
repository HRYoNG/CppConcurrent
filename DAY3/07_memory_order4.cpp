#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;
std::atomic<int> flag = 0;

void foo()
{
    data1.store(100, std::memory_order_relaxed);
    data2.store(200, std::memory_order_relaxed);

//  flag.store(1, std::memory_order_relaxed);
                    // => 위 코드가 이 한줄 아래로 내려올수 있습니다.

    flag.store(1, std::memory_order_release );
                    // => flag = 1
                    // => release 보다 위에 있는 코드는 
                    // => 반드시 acquire 이후에 적용이 되어 있어야 한다.
}

void goo()
{
    if ( flag.load( std::memory_order_acquire ) == 1 )
    {
        assert(data1.load(std::memory_order_relaxed) == 100);
        assert(data2.load(std::memory_order_relaxed) == 200);
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(goo);
    t1.join(); t2.join();
}