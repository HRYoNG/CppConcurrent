#include <iostream>
#include <chrono>

// chrono ���̺귯�� : �ð����� ���̺귯��(C++11)
// 14 page

int main()
{
	// �ٽ� 1. �ð� ���� Ÿ�� �˾Ƶμ���..
//	std::chrono::seconds s1 = 30;	// error. explicit ������
	std::chrono::seconds s2(30);	// ok

	std::chrono::nanoseconds ns(1);
	std::chrono::microseconds us(1);
	std::chrono::milliseconds ms(1);
	std::chrono::seconds ss(1);
	std::chrono::minutes m(1);
	std::chrono::hours   h(1);

	// C++20 ���� days, months, years Ÿ�Ե� �߰��Ǿ����ϴ�.
	

}
