#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

// �ٽ� : jthread�� ���޵Ǵ� ������ �Լ��� ���
// 1. f( ���ڵ� )
// 2. f( std::stop_token, ���ڵ� )

void foo( std::stop_token quit_token )
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

        if (quit_token.stop_requested())
            break;
    }
    std::cout << "finish foo" << std::endl;
}

void goo()
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "goo : " << i << std::endl;
    }
}
int main()
{
    std::jthread j1(&foo);  // �ٽ� - foo �Լ��� ��� ���ڵ� ������
                            //       �ʰ� �ֽ��ϴ�.
    std::jthread j2(&goo);

    std::this_thread::sleep_for(2s);

    j1.request_stop(); // ������ �޶�� ��û
    j2.request_stop(); // ������ �޶�� ��û ������ ó�� �ϴ� �ڵ尡 ����.
                        // ������ �ƴϰ�, �ƹ�ȿ���� ����.
}
// �ᱹ C++20 �� jthread ��
// 1. �Ҹ��ڿ��� �ڵ� join() ���
// 2. ������ ��� ���� �߰��� ��