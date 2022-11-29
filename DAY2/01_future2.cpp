#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// �� promise ��ü�� �ټ��� �����忡�� ���� ����Ҽ��ֳ��� ?
// => ���� ������ ���� �ϼ���..

void add(std::promise<int>& p, int a, int b)
{
    std::this_thread::sleep_for(1s);

    // �ٽ� 1. set_value() �� �ѹ��� �����մϴ�.
    p.set_value(a + b);
//  p.set_value(a + b); // ����!!!

    // ��, promise �� 1ȸ���Դϴ�.
    // ���� �����尡 ���� �ȵ˴ϴ�.
    // ���� �����尡 �����ϰų�, ������ ����� ��������
    // ���� ���ĺ��� ���� ����ȭ ����� ���� ����ϼ���..

    // ������ �Լ����� ��� �Ѱ��� ������ ������ : promise, packaged_task, async
    // ������ �Լ��� ������ ����Ÿ ��ȯ : �پ��� ����ȭ ������ ���� ����ϼ���
}

int main()
{
    std::promise<int> pm;

    // �ٽ� 2. promise ���� future �� �Ѱ��� ������ �ֽ��ϴ�.
    std::future<int> ft = pm.get_future();
//  std::future<int> ft2 = pm.get_future(); // ����!!

    // �ٽ� 3. future ��ü�� ���� �ȵ˴ϴ�.
//  std::future<int> ft2 = ft;  // error. 

    std::thread t(add, std::ref(pm), 10, 20);


    // �ٽ� 4. ft.get() �� �ѹ��� �����մϴ�.

    std::cout << ft.valid() << std::endl; // true
    int ret = ft.get();

    std::cout << ft.valid() << std::endl; // false
//  ret = ft.get(); // ���� �߻�


    t.join();
}



