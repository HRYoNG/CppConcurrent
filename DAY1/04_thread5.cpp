#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
using namespace std::literals;

// 스레드 우선 순위
// 대부분의 OS 에는 스레드 우선순위의 개념이 있습니다.

// 하지만, "std::thread"에는 우선순위를 다루는 멤버가 없습니다.

void foo()
{
    auto tid = std::this_thread::get_id(); // 스레드 ID 얻기
}

int main()
{
    std::thread t(&foo);

    // t가 관리하는 스레드의 OS 레벨의 핸들(디스크립터)얻기
    std::thread::native_handle_type handle = t.native_handle();

    // "native_handle_type" 의 타입은 구현마다 다릅니다.
    // 이제 OS 레벨의 핸들을 알면 가 OS 의 system call 을 사용가능합니다
    SetThreadPriority((HANDLE)handle, THREAD_PRIORITY_HIGHEST);

    t.join();
}

