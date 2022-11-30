#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> Q;

// 접근 동기화를 위한 mutex
std::mutex m;

// Q 가 비었을때 대기 하기 위한 condition_variable
std::condition_variable cv;



void producer()
{
	while (true)
	{
		static int cnt = 0;
		{
			std::lock_guard<std::mutex> g(m);

			Q.push(++cnt);

			std::cout << "producer : " << cnt << std::endl;
			if (cnt == 1000000) cnt = 0; 
		}
		cv.notify_one();
	}
}

void consume()
{
	while (true)
	{
		std::unique_lock<std::mutex> ul(m);

		// Q 가 비어있을때만 대기 하면 됩니다.
		// cv.wait(ul, !Q.empty()); // error. 2번째 인자로는 "bool"이 아닌
			   					    // 함수가 전달되어야 합니다.

		cv.wait(ul, [] {return !Q.empty(); }); 
								// => 이 예제는 Q.empty()로 조사하므로
								// => "data_ready" 같은 flag가 없어도 됩니다.

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
