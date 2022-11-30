// g++ reorder1.cpp –S –masm=intel -O2
// cl reorder1.cpp /FAs /c /O2

// godbolt.org 사이트에 접속해 보세요.. 
// => 다양한 언어의 코드를 컴파일한 결과의 어셈을 볼수 있는 사이트

#include <atomic>

int a = 0;
int b = 0;

// thread A
void foo()
{
    a = b + 1;

    std::atomic_thread_fence(std::memory_order_seq_cst);

    b = 1;
}

// thread B
void goo()
{
    if (b == 1)
    {
        // a == 1 을 보장할수 있을까 ?
    }
}






