#include <thread>

// copy, move

void foo() {}
void goo() {}

int main()
{
    std::thread t1(&foo);
    std::thread t2(&goo);

    // 1. swap() ��� �Լ�
    t1.swap(t2); // ok. 
                 // ���������δ� ������ �ڵ� swap

    //============================================
    // 2. copy �� �ȵǰ�, move �� ����
//  std::thread t3 = t1; // error
    std::thread t4 = std::move(t1); // ok

//  t1.join(); // ����!!. t1�� ������ �ڵ��� t4�� ���޵Ǿ���.

    t2.join();
    t4.join();


    //=============================================
    // 3. ��ü ������ �����ϱ�
    
    std::thread t5; // ���� ������ ���� �ȵ�

//  t5 = t4;            // error. ���� ���� �ȵ�.
//  t5 = std::move(t4); // ok. ��, t4�� ��ȿ �ϴٸ�.

    t5 = std::thread(&foo); // ok.. �� ����� �μ���.. ���� ����մϴ�.
        // => 1. �캯�� �ӽð�ü�� ����� ǥ���
        // => 2. �ӽð�ü�� rvalue �̹Ƿ� "move ���Կ�����" ȣ��

    t5.join();

}







void f1(std::thread t) 
{
    t.join(); 
}

std::thread f2()
{
    return std::thread(foo());
}
