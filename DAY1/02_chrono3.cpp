#include <iostream>
#include <chrono>
using namespace std::literals; // 30s, 3min, 3ns, 3ms ��������ϱ�����

void foo(std::chrono::seconds sec) {}

int main()
{
	// 30�ʸ� ��Ÿ���� ��ü�� ����� 2���� ���

	// ��� 1. Ÿ���� �̸��� ���� ���
	std::chrono::seconds s1(30);

	// ��� 2. "user define literals" �������� ������� ���̻� ���
	auto s2 = 30s; // std::chrono::seconds operator""s(30) �̶�� �Լ��� ȣ��˴ϴ�.

	// �Լ��� �ð��� �����ϴ� ���
	foo(30); // error. seconds Ÿ���� �ƴմϴ�.
	foo(std::chrono::seconds(30)); // ��� 1. 
	foo(30s);  // ��� 2.

	foo(20ns); // ĳ���� ���� ���� ����

}
