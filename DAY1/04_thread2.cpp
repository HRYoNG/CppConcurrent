#include <iostream>
#include <string>
#include <thread>

// OS�� �����ϴ� ������ �����Լ��� ����ϸ�
// => �����尡 �����ϴ� �Լ� ��翡 ������ �ֽ��ϴ�.(���� void* �Ѱ�)

// C++ thread : �����尡 �����ϴ� �Լ� ��翡�� ������ �����ϴ�.
void f1() { }
void f2(int a, double d) { }
void f3(int a, int& b, std::string&& s) { b = 100; }

int main()
{
    int n = 0;
    std::string s = "hello";

    // ���� ���� ���
    std::thread t1( &f1 );
    std::thread t2( &f2, 1, 3.4);

    // �ٽ� : ���ڸ� ������ �����Ҷ��� "std::ref()" �� ����մϴ�.
    // => ��, ���������� �ٸ� �������� ������ �����ϴ� ���� ���� �����մϴ�.
    std::thread t3( &f3, 1, std::ref(n), std::move(s) );

    t1.join();
    t2.join();
    t3.join();
}

