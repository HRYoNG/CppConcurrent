#include <iostream>
#include <atomic>
// trivial ���� ������
// => ����ڰ� ������ �ʰ�, �����Ϸ��� ����� �ִ� ����Ʈ ������ ����ϰ�
// => �����Լ��� ���� ���..
// => memcpy �� ���� �ϴ� �Ͱ� ������ ���

// atomic<T> : T�� ����(�̵�)�����ڰ� trivial �ؾ� �մϴ�.

struct Point
{
    int x, y;

    Point() = default;

//  Point(const Point& other ) : x(other.x), y(other.y) {}

    //Point(const Point&) = default;
};

std::atomic<Point> pt;


int main()
{
    Point ret = pt.load(); // Point Ÿ�Կ� ���� �����ڰ� �ִٸ�
                           // �ܼ��� �޸� ���簡 �ƴ�
                            // "���� �����ڸ� ȣ���ؼ� ���� �ؾ� �մϴ�."
}

