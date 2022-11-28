#include <iostream>
#include <thread>

// ������ �Լ��� ���
// 1. foo �� �Ϲ��Լ�
void foo(int a, double d) {}

// 2. Run �� ��� �Լ�
struct Machine
{
    void Run(int a, double d) {}
};

// 3. ()�����ڸ� �������� �Լ� ��ü
struct Work
{
    void operator()(int a, double b) const {}
};

int main()
{
    // 1. �Ϲ� �Լ�
    std::thread t1(&foo, 1, 3.4); // �Ϲ� �Լ��� �������

    // 2. ��� �Լ�
    Machine m;
    std::thread t2(&Machine::Run, &m, 1, 3.4);
                    // => m.Run(1, 3.4) �� ������� ����

    // 3. �Լ� ��ü
    Work w;
    w(1, 3.4); // () �����ڰ� ������ �Ǿ �Լ� ó�� ��밡��
    std::thread t3(w, 1, 3.4);
//  std::thread t3(&w, 1, 3.4);// ����!! error
                            // => w(1, 3.4) �� ������
                            // => (&w)(1, 3.4) �� ����

    // 4. ���� ǥ����
    std::thread t4([]() {std::cout << "lambda" << std::endl; });

    // ��� : ȣ�Ⱑ���� ��� ��(callable object)��
    //        ������� ���డ��.

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

