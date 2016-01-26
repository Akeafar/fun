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
		//мутация в случайную сторону каждого элемента:
		for (size_t i = 0; i < N; ++i)
			a[i] += ((rand() % 2 == 1) ? 1 : -1);

		//теперь выбираем лучших, отсортировав по возрастанию
		std::sort(a, a + N);
		//и тогда лучшие окажутся во второй половине массива.
		//скопируем лучших в первую половину, куда они оставили потомство, а первые умерли:
		std::copy(a + N / 2, a + N, a);
		//теперь посмотрим на среднее состояние популяции. Как видим, оно всё лучше и лучше.
		std::cout << std::accumulate(a, a + N, 0) / N << std::endl;
	}
}