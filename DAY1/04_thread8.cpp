#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
    // �ٽ� 1. thread �����ϸ� �ݵ�� join() �Ǵ� detach()�ؾ� �մϴ�.
    std::thread t1(&do_work, 1);
    t1.join();

    //==========================================
    // �ٽ� 2. vector �� 10���� ������ �����ϱ�

    std::vector<std::thread> v; // ũ�Ⱑ 0�� vector

    for (int i = 0; i < 10; i++)
    {
        // ��� 1. thread ��ü ������ move �� �ֱ�
//      std::thread t(&do_work, 3);
//      v.push_back(t); // error. ���� ������ ����ϴµ� copy �ȵ�.
//      v.push_back( std::move(t) ); // ok

        // ��� 2. �ӽð�ü�� �ֱ�
//      v.push_back( std::thread(&do_work, 3) );  // ok

        // ��� 3. emplace_back ��� - ���� ���� ���
        // => std::thread �� ��ü�� ���� ������ ����
        // => std::thread �� ����� ���� ���ڸ� ����
        v.emplace_back( &do_work, 3 );
                // => ���������� std::thread(&do_work, 3)���θ���
                //    ���ۿ� ����
    }
    std::for_each(v.begin(), v.end(), [](auto& t) { t.join(); });


}
