// 4번을 3번으로 옮기세요
#include <iostream>
#include <thread>
#include <atomic>

struct Point   { int x, y; };    // 64bit 구조체
struct Point3D { int x, y, z; }; // 96bit 구조체

std::atomic<int>   a1;
std::atomic<Point> a2;
std::atomic<Point3D> a3;

int main()
{
    // 아래 코드는 모두 멀티 스레드에 안전하게 동작합니다.
    ++a1;
    int n = a1.load();
    Point pt1 = a2.load();
    Point3D pt2 = a3.load(); // 역시 멀티스레드에 안전합니다.


    // lock-free 로 동작하는가 확인
    std::cout << a1.is_lock_free() << std::endl;
    std::cout << a2.is_lock_free() << std::endl;
    std::cout << a3.is_lock_free() << std::endl;
                // => false,  일부 컴파일러는 에러가 나오는 경우가 있습니다.
                // => lock-free 가 안되는 경우 구현에 따라 다를수 있지만
                // => spin lock(busy waiting)를 사용하는 경우가 많습니다.
}

