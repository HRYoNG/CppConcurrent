#include <thread>
#include <atomic>

std::atomic<int> x = 0;
std::atomic<int> y = 0;

// std::memory_order_relaxed
// => 접근 만 동기화되면 된다는 의미 입니다.
// => reordering 이 발생할수 있습니다.

void foo()
{
    int n1 = y.load(std::memory_order_relaxed);
    x.store(n1, std::memory_order_relaxed);
                // => x = n1 이 동시접근에 대해서는 안전 합니다.
                // => 하지만 위 코드가 아래로 내려올수도 있습니다
}



void goo()
{
    int n2 = x.load(std::memory_order_relaxed);
    y.store(100, std::memory_order_relaxed);
}

int main()
{
    std::thread t1(foo);
    std::thread t2(goo);
    t1.join(); t2.join();
}