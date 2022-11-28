#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
    std::vector<std::thread> v1; 

    for (int i = 0; i < 10; i++)
    {
        v1.emplace_back(&do_work, 3);
    }
    std::for_each(v1.begin(), v1.end(), [](auto& t) { t.join(); });


}
