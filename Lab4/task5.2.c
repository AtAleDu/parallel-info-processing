#include <stdio.h>
#include <omp.h>

int main(void)
{
	int k;
	int N;
	long long sum = 0;

	if (scanf("%d", &k) != 1 || scanf("%d", &N) != 1 || k <= 0 || N <= 0) {
		printf("Error\n");
	}
	else
	{
#pragma omp parallel num_threads(k) reduction(+:sum)
		{
			int id = omp_get_thread_num();      //Номер потока
			int threads = omp_get_num_threads();//Количество потоков
			long long local_sum = 0;

			for (int i = id + 1; i <= N; i += threads)
				local_sum += i;

			printf("[%d]: Sum = %lld\n", id, local_sum);

			sum += local_sum;
		}

		printf("Sum = %lld\n", sum);
	}

	return 0;
}