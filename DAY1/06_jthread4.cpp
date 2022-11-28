#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

void foo(bool& flag)
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

        // ���ο� ������� �ֱ������� cancel flag �� Ȯ���մϴ�.
        if (flag == true)
            break;
    }
    // ����ϴ� �ڿ����� release �ϰ�  ���� �մϴ�.

    std::cout << "finish foo" << std::endl;

    return;
}

int main()
{
    bool quit = false;

    std::thread t(foo, std::ref(quit));

    std::this_thread::sleep_for(2s);

    quit = true;    // �����ߴ� ������ ����!!

    t.join();
}