#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void divide(std::promise<int>& p, int a, int b)
{
    if (b == 0)
    {
        // ���ܴ� ���� �����忡���� ���� �����մϴ�.
        // �Ʒ� �ڵ�� �ֽ����忡 ���޵ɼ� �����ϴ�.
        throw std::runtime_error("divide by zero");
    }
    p.set_value(a / b);
}

int main()
{
    std::promise<int> pm;
    std::future<int>  ft = pm.get_future();

    std::thread t(divide, std::ref(pm), 10, 2);


    int ret = ft.get();

    t.join();
}



