#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals;


// yield() �� ����ؼ� sleep() �����
// system_clock : 
// high_resolution_clock : ���� ������ �ð�
//                         ���� ��κ� system_clock �� ����
void mysleep(std::chrono::microseconds us)
{
    auto target = std::chrono::high_resolution_clock::now() + us;

    while (std::chrono::high_resolution_clock::now() < target)
        std::this_thread::yield();
}

int main()
{
    mysleep(1s);
}

// cpu Ÿ���� �󸶳� ��Ȯ�� ���ΰ��� ? => OS ���� �ٸ��ϴ�.
// windows : GetQueryPerformanceCounter() ��� API �� ����մϴ�.
//