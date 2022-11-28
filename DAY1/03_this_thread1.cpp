#include <iostream>
#include <thread>   // C++11 ���� ���� �Ǵ� ���
#include <vector>
#include <unordered_set>

// std::this_thread ��� namespace �ȿ� 4���� ���� �Լ��� �ֽ��ϴ�.

int main()
{
    // 1. get_id()�� ������ ID ���. 
    std::cout << std::this_thread::get_id() << std::endl;


    std::thread::id tid1 = std::this_thread::get_id();
    // class thread
    // {
    //      using id = ������ ���� �ٸ��� ���� "struct thread_id{}"
    // } 

    // ������ id Ư¡
    // 1. int ��ȯ �ȵ˴ϴ�.
    int n1 = tid1;  // error

    // 2. container �� ���� �����ϰ�, 
    //    hash �����ϹǷ� unordered_set �� �������ֽ��ϴ�
    std::vector<std::thread::id> v;
    std::hash<std::thread::id> h;
    std::unordered_set<std::thread::id> s;

    // 3. ����(==, !=) �����մϴ�.
    auto t1 = std::this_thread::get_id();
    auto t2 = std::this_thread::get_id();

    bool b1 = t1 == t2;
    bool b1 = t1 != t2;
}
// �ٽ� : ������ ID �� ���� ��� ���������� ������
//       "std::thread::id" Ÿ�� �Դϴ�.
