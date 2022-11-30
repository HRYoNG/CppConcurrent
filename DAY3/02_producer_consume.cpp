#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> Q;	// STL 컨테이너는 멀티 스레드 환경에 안전하지 
					// 않습니다.

// 아래 코드는 동기화 되지 않으므로 비정상 종료 됩니다.

void producer()
{
	while (true)
	{
		static int cnt = 0;
		Q.push(++cnt);
		std::cout << "producer : " << cnt << std::endl;
		if (cnt == 1000000) cnt = 0;
	}	
}
void consume()
{
	while (true)
	{
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
