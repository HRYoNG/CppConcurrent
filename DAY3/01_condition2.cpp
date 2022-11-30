#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;


std::mutex m;
int shared_data = -1; 

// 1. condition_variable Ÿ���� ���������� �����մϴ�.
std::condition_variable cv;


void consumer()
{
    // 2. ��ȣ�� ����ϴ� �������  unique_lock ���� ���ؽ� ȹ���� 
    //    ��ȣ�� ��� �մϴ�.
    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);    // 1. ul.unlock() ���� lock �� Ǯ��
                    // 2. cv �� ���ؼ� ��ȣ�� �ö� ���� ��� �մϴ�
                    // 3. ��ȣ�� ���� �����, ul.lock() ���� �ٽ�
                    //    ���ؽ� ȹ����.. ���� �ڵ� ����


    std::cout << "consume : " << shared_data << std::endl;
}




void producer()
{
    std::this_thread::sleep_for(10ms);
    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }
    // 3. ��ȣ�� �ִ� ������� unique_lock �� ������� �ʾƵ� �˴ϴ�.
    // �����ڿ��� �غ� �Ǹ� ��ȣ�� �ָ� �˴ϴ�.
    // ���ǻ����� "��ȣ�� �ֱ����� unlock" �ϰ� ��ȣ�� �ּ���
    cv.notify_one();
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}