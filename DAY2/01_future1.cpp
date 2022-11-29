#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// QA 1. ǻó��ü�� ���ι̽� ��ü���� �޾ƿͼ� �����Ǵ� �ǵ� �� ���� ���ι̽��� �����ʰ� 
// ǻó��ü�� ���� ����ϴ� ������ �� ���� Ȥ�� ������ �ֳ���?
// promise - future
// packaged_task - future
// async - future

// QA 2. ft.get() �� ���ѷ��� ���鼭 ����ϳ���
// => ������ ���� �ٸ��ϴ�. C++ ǥ�ؿ��� ������ ������� �ʾҽ��ϴ�.
// => ��κ��� ���� ������ �ƴϷ� CPU cycle �� ���� ����ϴ� ������ ����մϴ�.

// QA 3. Ÿ�Ӿƿ��� �ɼ��ֳ��� ?
// => ���� ����!!!

void add(std::promise<int>& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}
int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::ref(pm), 10, 20);

//  int ret = ft.get(); // ����� ���ö� ���� ������ ��� �մϴ�.


    std::future_status ret = ft.wait_for(2s); // 2�ʱ����� ���

    if (ret == std::future_status::ready)
    {
        std::cout << "set_value() �� �Ǿ ��� �غ��" << std::endl;
        std::cout << ft.get() << std::endl; // ����� �̹� �����Ƿ�
                                            // ��� ���� ����
    }
    else if (ret == std::future_status::timeout)
    {
        std::cout << "timeout" << std::endl;
    }
    else if (ret == std::future_status::deferred)
    {
        std::cout << "������ ���� ����ȵ�" << std::endl;
        std::cout << "async()�� ��ȯ�� future ���� Ư¡" << std::endl;
    }







    t.join();
}



