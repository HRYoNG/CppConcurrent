#include <iostream>
#include <atomic>
// trivial 복사 생성자
// => 사용자가 만들지 않고, 컴파일러가 만들어 주는 디폴트 버전을 사용하고
// => 가상함수가 없는 경우..
// => memcpy 로 복사 하는 것과 동일한 경우

// atomic<T> : T의 복사(이동)생성자가 trivial 해야 합니다.

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
    Point ret = pt.load(); // Point 타입에 복사 생성자가 있다면
                           // 단순히 메모리 복사가 아닌
                            // "복사 생성자를 호출해서 복사 해야 합니다."
}

