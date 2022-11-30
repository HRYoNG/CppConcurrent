#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;

int main()
{
    // std::memory_order_seq_cst : �ݵ�� ���������� ����Ǿ�� �Ѵ�.
    //                          => ���� ������尡 �����ϴ�.
    data1.store(100, std::memory_order_seq_cst);
    data2.store(200, std::memory_order_seq_cst);
    data2.store(300);  // ����Ʈ���� std::memory_order_seq_cst �Դϴ�.
}
// C++�� memory order �� �߻�ȭ �����Դϴ�.
// => �ش� ����� ��� ���������� "�� CPU ȯ��" �� ���� �޶� ���ϴ�.

// relaxed : ���� ���ٸ� ���� �ʰ�
// release-acquire : release������ �ڵ�� acquire ���Ŀ� Ȯ�� ����!
// seq_cst : ���� ����