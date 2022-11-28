#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

constexpr std::size_t sz = 1'000'000;

std::vector<int> v;

void init()
{
    for (int i = 0; i < sz; ++i)
    {
        v.push_back(i);
    }
}


// ������ ���� ���ϴ� �Լ�.
template<typename IT, typename RT> 
void sum(IT first, IT last, RT& result)
{
    result = std::accumulate(first, last, result);
}

int main()
{
    init();
    int s = 0;    

//  sum( v.begin(), v.end(), s);    // �ֽ����尡 ����


//  std::thread t(sum, v.begin(), v.end(), std::ref(s)); // error
                        // => �� �����ϱ�� ?
                        // => sum �� ���ø� �ε�, ���� ȣ���� �ƴϹǷ�
                        // => IT�� RT Ÿ���� �߷��� �ȵ˴ϴ�.

    std::thread t(sum<std::vector<int>::iterator, int>, 
                  v.begin(), v.end(), std::ref(s));

    t.join();


    std::cout << s << std::endl;
}