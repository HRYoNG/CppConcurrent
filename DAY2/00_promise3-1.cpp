#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// promise
// => ������ �����尡 "��" �� "����" �� �θ� �����忡�� �����Ҽ� �ִ� ����
// => future ��ü�� ���ؼ� "��"�� "����"�� ��� �Ҽ� �ִ�.


void divide(std::promise<int>& p, int a, int b)
{
    try
    {
        if (b == 0)
        {
            throw std::runtime_error("divide by zero");
        }
        p.set_value(a / b);
    }
    catch (...)
    {
        // ���� �߻��� ���ܸ� promise �� ���ؼ� 
        // �ֽ�����(future ��ü�� ������ ������)�� �����մϴ�.
        p.set_exception( std::current_exception() );
    }
}

int main()
{
    std::promise<int> pm;
    std::future<int>  ft = pm.get_future();

    std::thread t(divide, std::ref(pm), 10, 0 );

    try
    {
        int ret = ft.get();
    }
    catch (...)
    {
        std::cout << "�����尡 �����߿� ���� �߻�" << std::endl;
    }

    t.join();
}



