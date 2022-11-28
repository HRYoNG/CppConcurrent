#include <iostream>
#include <chrono>

int main()
{
	// ��ȯ �̾߱� 
	std::chrono::seconds s(70); // 70 ��

	std::cout << s.count() << std::endl; // 70


	// "nano �� = ��"�� ����Ÿ �ս��� �����ϴ�.
	// �Ʒ��� ���� �׳� ����(����) �˴ϴ�.
	std::chrono::nanoseconds n = s;

	std::cout << n.count() << std::endl; // 70000000000 


	// "�� = ��" �� ����Ÿ �ս��� �ֽ��ϴ�.
	// ����� ĳ������ �ʿ� �մϴ�.
	// std::chrono::minutes m = s;	// error

	std::chrono::minutes m =
		std::chrono::duration_cast<std::chrono::minutes>(s);


	std::cout << m.count() << std::endl; // 1

//	using namespace std::chrono; // �̷��� �ϸ� namespace �̸�
								// ���� ��밡��������
								// ������ �������� �ʽ��ϴ�.
								// �̸� �浹 �߻�
}
