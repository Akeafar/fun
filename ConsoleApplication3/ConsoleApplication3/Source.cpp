#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <numeric>

int main()
{
	srand((unsigned int)time(NULL));
	const size_t N = 10;
	int a[N] = { 0 };
	for (;;)
	{
		//������� � ��������� ������� ������� ��������:
		for (size_t i = 0; i < N; ++i)
			a[i] += ((rand() % 2 == 1) ? 1 : -1);

		//������ �������� ������, ������������ �� �����������
		std::sort(a, a + N);
		//� ����� ������ �������� �� ������ �������� �������.
		//��������� ������ � ������ ��������, ���� ��� �������� ���������, � ������ ������:
		std::copy(a + N / 2, a + N, a);
		//������ ��������� �� ������� ��������� ���������. ��� �����, ��� �� ����� � �����.
		std::cout << std::accumulate(a, a + N, 0) / N << std::endl;
	}
}