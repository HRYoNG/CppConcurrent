#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

// �۾�3�� ������ ������ �Լ�
void work(std::promise<int>& p, std::vector<int>& v)
{
    int s = std::accumulate(v.begin(), v.end(), 0);

    p.set_value(s);
}


int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

    // �۾� 1. v1�� �κ����� ���ؼ� v2�� �ֱ�
    std::partial_sum(v1.begin(), v1.end(), v2.begin());

    //=============================================
    // �����带 �����ؼ�. "�۾�3"�� �����ϵ����մϴ�.
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    std::thread t(work, std::ref(p), std::ref(v2) );


    //============================================
    // �۾� 2. v2 �� ��� ��Ҹ� ȭ�� ���
    for (auto n : v2)
        std::cout << n << ", ";

    // �����尡 �����ϴ� �۾�3�� ����� ����մϴ�.
    int s = ft.get();

    std::cout << "\n" << s << std::endl;

    t.join();
}

// �۾�1 �� ����Ǿ�߸� �۾�2, �۾�3�� �Ҽ� �ֽ��ϴ�.
// �۾�2�� �۾�3�� ������ �۾��Դϴ�.
// => �ð��� ���� �ɸ��� �۾��̸� 2���߿� �Ѱ��� ������� �����ص� �˴ϴ�.


