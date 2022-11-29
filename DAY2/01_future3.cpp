#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}
int main()
{
    std::promise<int> pm;
    
    std::future<int> ft = pm.get_future();

    // �ٽ�1 : future �� �ѹ��� ������ �ְ�, ���絵 �ȵ˴ϴ�.
//  std::future<int> ft2 = pm.get_future(); // ����
//  std::future<int> ft2 = ft; // error.

    // �ٽ� 2. future ���� shared_future�� ������ �ֽ��ϴ�
    // => �ѹ��� ������ �ֽ��ϴ�.
    // => ������, shared_future �� ���� �����մϴ�.
    std::shared_future<int> sf1 = ft.share();
//  std::shared_future<int> sf2 = ft.share(); // ����
    std::shared_future<int> sf2 = sf1;
    std::shared_future<int> sf3 = sf1;
    
    std::thread t(add, std::ref(pm), 10, 20);

    // �ٽ� 3. �ϳ��� promise �� ���ؼ� 3���� "shared_future"�� ������
    // 3���� �����尡 ����� ��� �Ҽ� �ֽ��ϴ�.
//  std::thread t1(&f1, sf2); // ������ ������ �ǰ� ������ ������ �˴ϴ�.
//  std::thread t2(&f2, sf3);

    
    // �ٽ� 4. future ���� shared_future�� ���� ����
    // �ֽ����嵵 �ݵ�� shared_futre�� ����ؾ� �մϴ�.
    // ����, �Ʒ�ó�� "future"�� ����ϸ� 
    // => shared_future �� ����ؼ� get()�ϴ� ��� �ڵ�� ���� �Դϴ�.
//  int ret1 = ft.get();    // shared_future�� ������ ���� ��츸 ���


    int ret1 = sf1.get();  // shared_future�� ���� ���.

    t.join();
}




