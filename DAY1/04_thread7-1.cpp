#include <thread>

void foo() {}
void goo() {}

void f1(std::thread t) {   t.join();}

std::thread f2()       { return std::thread(&foo);}

int main()
{
    // �ٽ� 1. �Լ� ���ڷ� ������ ��ü �����ϱ�
    std::thread t1(&foo);

//  f1(t1);             // error. copy �ɼ� ����.
    f1(std::move(t1));  // ok
    f1(std::thread(&foo)); // ok. �ӽð�ü�� rvalue!

    // �ٽ� 2. std::thread �� ��ȯ�ϴ� �Լ�
    std::thread t2 = f2(); // ok
                // => 1. f2() �� �� ��ȯ �Դϴ�.
                // => 2. �ӽð�ü�� ��ȯ �˴ϴ�.
                // => 3. �ӽð�ü�� rvalue �̰� move ������ ȣ��
    t2.join();

}



