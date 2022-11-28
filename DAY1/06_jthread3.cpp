#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

void foo(int a, int b)
{
    std::cout << "foo : " << a << ", " << b << std::endl;

    std::this_thread::sleep_for(3s);
}  

int main()
{
    // �ٽ� 1. std::thread �� join �Ǵ� detach �ʿ�
//  std::thread t1(&foo, 10, 20);
//  std::thread t2(&foo, 10, 20);

//  t1.join();
//  t2.join();

    // �ٽ� 2. C++20 jthread �� �Ҹ��ڿ��� �ڵ����� join ����
    std::jthread jt1(&foo, 10, 20);
    std::jthread jt2(&foo, 10, 20);

} // <== �̼��� jt1, jt2�� �ı�, �Ҹ��ڿ��� �ڵ����� .join() ȣ��

// g++ �ҽ�.cpp -std=c++20