#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
    std::vector<std::thread> v1; 
    std::vector<std::thread> v2(10); // 스레드 객체는 만들었지만
                                     // 스레드는 아직 생성 안됨


    for (int i = 0; i < 10; i++)
    {
        v1.emplace_back(&do_work, 3);

        v2[i] = std::thread(&do_work, 3); // 이순간 스레드 시작
    }

    std::for_each(v1.begin(), v1.end(), [](auto& t) {t.join();});
    std::for_each(v2.begin(), v2.end(), [](auto& t) {t.join();});
}
