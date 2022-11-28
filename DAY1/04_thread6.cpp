#include <iostream>
#include <thread>

void foo() {}

int main()
{
//  std::thread t1(&foo);   // ������ ������
//  t1.join(); // ok.. 


    std::thread t2; // �Լ��� �������� �ʾҽ��ϴ�.
                    // ������ �������� �ʽ��ϴ�

    try
    {
        t2.join();  // ���� �߻�!
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    // ��ó�� ���� ó���ϰų�
    // �Ʒ� ó�� ���� ���� �ϼ���!
    if (t2.joinable())
        t2.join();

    // 1. �����带 �������� �ʾҰų� 
    // 2. detach()�� �и��߰ų�
    // 3. �̹� join() �� �߰ų�!!
    // 1~3�� ��쿡 �ٽ� .join()�ϸ� ���� �Դϴ�.
}
