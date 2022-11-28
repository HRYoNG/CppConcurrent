#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
    // 핵심 1. thread 생성하면 반드시 join() 또는 detach()해야 합니다.
    std::thread t1(&do_work, 1);
    t1.join();

    //==========================================
    // 핵심 2. vector 로 10개의 스레드 관리하기

    std::vector<std::thread> v; // 크기가 0인 vector

    for (int i = 0; i < 10; i++)
    {
        // 방법 1. thread 객체 생성후 move 로 넣기
//      std::thread t(&do_work, 3);
//      v.push_back(t); // error. 복사 생성자 사용하는데 copy 안됨.
//      v.push_back( std::move(t) ); // ok

        // 방법 2. 임시객체로 넣기
//      v.push_back( std::thread(&do_work, 3) );  // ok

        // 방법 3. emplace_back 사용 - 가장 좋은 방법
        // => std::thread 의 객체를 만들어서 보내지 말고
        // => std::thread 를 만들기 위한 인자를 전달
        v.emplace_back( &do_work, 3 );
                // => 내부적으로 std::thread(&do_work, 3)으로만들어서
                //    버퍼에 보관
    }
    std::for_each(v.begin(), v.end(), [](auto& t) { t.join(); });


}
