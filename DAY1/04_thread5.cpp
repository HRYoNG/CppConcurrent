#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
using namespace std::literals;

// ������ �켱 ����
// ��κ��� OS ���� ������ �켱������ ������ �ֽ��ϴ�.

// ������, "std::thread"���� �켱������ �ٷ�� ����� �����ϴ�.

void foo()
{
    auto tid = std::this_thread::get_id(); // ������ ID ���
}

int main()
{
    std::thread t(&foo);

    // t�� �����ϴ� �������� OS ������ �ڵ�(��ũ����)���
    std::thread::native_handle_type handle = t.native_handle();

    // "native_handle_type" �� Ÿ���� �������� �ٸ��ϴ�.
    // ���� OS ������ �ڵ��� �˸� �� OS �� system call �� ��밡���մϴ�
    SetThreadPriority((HANDLE)handle, THREAD_PRIORITY_HIGHEST);

    t.join();
}

