#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex       m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

int main()
{
    // �ٽ� 1. ���� ���
    std::unique_lock<std::mutex> u1;     // ���� mutex ����ȵ�
    std::unique_lock<std::mutex> u2(m1); // �����ڿ��� m1.lock()                 
    std::unique_lock<std::mutex> u3(m2, std::try_to_lock);
                                        // �����ڿ��� m2.try_lock()
                                        // lock �� ȹ������ ���ص� ��� ����

    // �ٽ� 2. lock �� ���� �ߴ��� ����
    if (u3.owns_lock())
        std::cout << "acquire lock" << std::endl;
    else
        std::cout << "fail to lock" << std::endl;


    // �ٽ� 3. �̹� ȹ���� mutex �� ���� unlock ��ɸ� ����ϴ� ���
    m3.lock();
    std::unique_lock<std::mutex> u4(m3, std::adopt_lock);   


    // �ٽ� 4. �����ڿ��� lock ��������, ���߿� lock �� �� ���
    // => ����, timed_mutex �� ���� try_lock_for ��
    //    unique_ptr�� ����
    std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock);
    auto ret = u5.try_lock_for(2s);


    // �ٽ� 5. timed_mutex �� �����ϸ� 2��° ���ڷ� chrono Ÿ�� ���� ����

    std::unique_lock<std::timed_mutex> u6(tm2, 2s);  // tm2.try_lock_for(2s) ���
    std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s);
    // tm3.try_lock_until() ���
}
