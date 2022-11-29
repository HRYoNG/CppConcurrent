#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Object
{
    int member_data;
public:
    Object()
    {
        std::cout << "start ctor" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish ctor" << std::endl;
    }
    void init()
    {
        std::cout << "start init" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish init" << std::endl;
    }
};

void foo()
{
    // �ٽ� 1. �������� - ������ ���� ���� �����˴ϴ�.
    // => ������� ���� ��ü�� ����
    // => �����ڵ� ���� ȣ��
    // => ����Ÿ�� ���� ����ϹǷ� ���ÿ� ����Ǿ ����
    Object obj1;


    // �ٽ� 2. static ��������, 
    // => �����尡 ������ ����Ǿ ��ü�� �Ѱ�
    // => ������ ȣ���� ����ȭ ��.
    // => ���� ������ �����常 ������ ȣ��. ���� ������ ������� ���.
    static Object obj2;


    // �ٽ� 3. �Ϲ� ��� �Լ� ȣ���� ����ȭ ���� �ʽ��ϴ�.
    // => �����尡 ���� �Ʒ� init ȣ��
    // => ����ȭ �ʿ� �ϰų�, �ѹ��� ȣ��ǰ� �Ϸ��� call_once ���.
    obj2.init();


    // �ٽ� 4. ��ü�� �������� ����
    // => ����, ������ ���� ���� ��ü ����
    // => �����ڵ� ���ÿ� ����
    Object* p = new Object;
    delete p;
}



int main()
{
    std::thread t1(&foo);
    std::thread t2(&foo);

    t1.join();
    t2.join();
}



