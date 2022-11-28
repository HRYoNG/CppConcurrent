#include <thread>

// copy, move

void foo() {}
void goo() {}

int main()
{
    std::thread t1(&foo);
    std::thread t2(&goo);

    // 1. swap() 멤버 함수
    t1.swap(t2); // ok. 
                 // 내부적으로는 스레드 핸들 swap

    //============================================
    // 2. copy 는 안되고, move 는 가능
//  std::thread t3 = t1; // error
    std::thread t4 = std::move(t1); // ok

//  t1.join(); // 예외!!. t1의 스레드 핸들은 t4에 전달되었음.

    t2.join();
    t4.join();


    //=============================================
    // 3. 객체 생성후 실행하기
    
    std::thread t5; // 아직 스레드 생성 안됨

//  t5 = t4;            // error. 복사 대입 안됨.
//  t5 = std::move(t4); // ok. 단, t4가 유효 하다면.

    t5 = std::thread(&foo); // ok.. 꼭 기억해 두세요.. 자주 사용합니다.
        // => 1. 우변은 임시객체를 만드는 표기법
        // => 2. 임시객체를 rvalue 이므로 "move 대입연산자" 호출

    t5.join();

}







void f1(std::thread t) 
{
    t.join(); 
}

std::thread f2()
{
    return std::thread(foo());
}
