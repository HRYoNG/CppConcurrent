#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

std::condition_variable cv;

// �Ʒ� �ڵ��� ������ 
// => �����ڰ� �Һ��� ���� ���� ���� �մϴ�.
// => �Һ��ڰ� wait �ϱ� ���� �����ڰ� signal �� ������ �˴ϴ�.

void consumer()
{
    std::this_thread::sleep_for(10ms);

    std::unique_lock<std::mutex> ul(m);

    cv.wait(ul);    // <= �̹� cv.notify_xxx() ���Ŀ� 
                    // <= �ʰ� �����ؼ� wait �ϰ� �ֽ��ϴ�.
                    //    �ٽ� cv.notify_xxx() �� �Ҷ� ���� ����ϰ� �˴ϴ�.
                    // �ذ�å�� "conditio4" ����!!

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{

    {
        std::lock_guard<std::mutex> lg(m);
        shared_data = 100;
        std::cout << "produce : " << shared_data << std::endl;
    }

    cv.notify_one();
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}