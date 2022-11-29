#include <mutex>

// C++ ���� mutex�� 6�� �Դϴ�.
// C++ ���� lock management ������ 4�� �Դϴ�.

// 1. std::lock_guard : ���� ������, �ܼ��� ���. �����ڿ� �Ҹ��ڸ� �ֽ��ϴ�.


// 2. std::unique_lock : ���� ����� �����ϴ�.
//						std::condition_variable �� ����Ϸ��� �ʿ� �մϴ�.

// 3. std::shared_lock : shared_mutex �� ���� ����. 
//						 �����ڿ��� lock_shared()
//						 �Ҹ��ڿ��� unlock_shared()

// 4. std::scoped_lock : 2�� �̻��� ���ؽ��� ���ÿ� lock �Ҷ�



std::mutex m;

int main()
{
	// lock_guard �� ����ϴ� 2���� ���
	// 1. �����ڿ��� lock ȹ��
	{
		std::lock_guard<std::mutex> lg(m);
	}

	// 2. �̹� lock ȹ���� ������ ���ؽ� ����
	if (m.try_lock())
	{
		std::lock_guard<std::mutex> lg(m, std::adopt_lock);
	}	
}



