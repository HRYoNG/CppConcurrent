#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;

int main()
{
    // std::memory_order_seq_cst : 반드시 순차적으로 실행되어야 한다.
    //                          => 가장 오버헤드가 많습니다.
    data1.store(100, std::memory_order_seq_cst);
    data2.store(200, std::memory_order_seq_cst);
    data2.store(300);  // 디폴트값이 std::memory_order_seq_cst 입니다.
}
// C++의 memory order 는 추상화 개념입니다.
// => 해당 명령을 어떻게 구현할지는 "각 CPU 환경" 에 따라 달라 집니다.

// relaxed : 동시 접근만 되지 않게
// release-acquire : release이전의 코드는 acquire 이후에 확인 가능!
// seq_cst : 순차 실행