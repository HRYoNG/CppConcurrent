#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// �Ʒ� �ڵ�� "Q�� ���� ����" ������ ���� �ɼ��ֽ��ϴ�.
// => �ذ��� ������.. !!


std::queue<int> Q;

// ���� ����ȭ�� ���� mutex
std::mutex m;

// Q �� ������� ��� �ϱ� ���� condition_variable
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

		// Q �� ����������� ��� �ϸ� �˴ϴ�.
		// cv.wait(ul, !Q.empty()); // error. 2��° ���ڷδ� "bool"�� �ƴ�
			   					    // �Լ��� ���޵Ǿ�� �մϴ�.
		 
		cv.wait(ul, [] {return !Q.empty(); }); 
								// => �� ������ Q.empty()�� �����ϹǷ�
								// => "data_ready" ���� flag�� ��� �˴ϴ�.

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


// cv.wait(ul, [] {return !Q.empty(); });
// => 1. �Լ� ������ ����� true �̸� ��� ����
// => 2. ����� false �̸� ���(wait)
// => 3. ��ȣ�� ����.!! 1�� �ٽ� ����(��, �ٽ� �Լ� ����)