#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

    // �۾� 1. v1�� �κ����� ���ؼ� v2�� �ֱ�
    std::partial_sum(v1.begin(), v1.end(), v2.begin()); 

    // �۾� 2. v2 �� ��� ��Ҹ� ȭ�� ���
    for (auto n : v2)
        std::cout << n << ", ";

    // �۾� 3. v2�� ��� ����� ���� ���ϱ�
    int s = std::accumulate(v2.begin(), v2.end(), 0);
    
    // �۾� 4. ��� ���
    std::cout << "\n" << s << std::endl;
}



