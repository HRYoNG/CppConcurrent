#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> Q;	

// 접근 동기화를 위한 mutex
std::mutex m;


// 아래 코드는 Q 의 동시접근은 해결했지만
// 문제 점은 Q가 비어 있을때입니다.
// => Q가 비어 있다면 "소비자는 대기" 해야 합니다.

void producer()
{
	while (true)
	{
		static int cnt = 0;

		std::lock_guard<std::mutex> g(m);

		Q.push(++cnt);

		std::cout << "producer : " << cnt << std::endl;
		if (cnt == 1000000) cnt = 0;
	}
}

void consume()
{
	while (true)
	{
		std::lock_guard<std::mutex> g(m);
		int element = Q.front();
		Q.pop();
		std::cout << "\tconsume : " << element << ", current Q size : " << Q.size() << std::endl;
	}
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consume);

	t1.join();
	t2.join();
}
