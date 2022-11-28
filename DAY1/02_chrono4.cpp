#include <iostream>
#include <chrono>
#include <string>

int main()
{
    // 1. ���� �ð��� ��� ���
    //    "std::chrono::system_clock" Ŭ������ ���� ��� �Լ� "now"���
    
    // time_point : ���ؽð����� ���� "�󸶳� ���" �ߴ°�..

    std::chrono::system_clock::time_point tp =
                                std::chrono::system_clock::now();

    // epoch_time : ���� �ð��� 1970�� 1�� 1�� ���� �� �������� �ϴ� �ð�
    std::chrono::nanoseconds ns = tp.time_since_epoch();
    
    std::chrono::seconds ss = 
        std::chrono::duration_cast<std::chrono::seconds>(ns);


    std::chrono::hours hh = 
        std::chrono::duration_cast<std::chrono::hours>(ns);

    std::cout << ns.count() << std::endl;
    std::cout << ss.count() << std::endl;
    std::cout << hh.count() << std::endl;
}