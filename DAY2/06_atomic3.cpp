// 4���� 3������ �ű⼼��
#include <iostream>
#include <thread>
#include <atomic>

struct Point   { int x, y; };    // 64bit ����ü
struct Point3D { int x, y, z; }; // 96bit ����ü

std::atomic<int>   a1;
std::atomic<Point> a2;
std::atomic<Point3D> a3;

int main()
{
    // �Ʒ� �ڵ�� ��� ��Ƽ �����忡 �����ϰ� �����մϴ�.
    ++a1;
    int n = a1.load();
    Point pt1 = a2.load();
    Point3D pt2 = a3.load(); // ���� ��Ƽ�����忡 �����մϴ�.


    // lock-free �� �����ϴ°� Ȯ��
    std::cout << a1.is_lock_free() << std::endl;
    std::cout << a2.is_lock_free() << std::endl;
    std::cout << a3.is_lock_free() << std::endl;
                // => false,  �Ϻ� �����Ϸ��� ������ ������ ��찡 �ֽ��ϴ�.
                // => lock-free �� �ȵǴ� ��� ������ ���� �ٸ��� ������
                // => spin lock(busy waiting)�� ����ϴ� ��찡 �����ϴ�.
}

