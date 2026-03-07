#include <stdio.h>
#include <omp.h>

int main(void) {
    int N = 0;

    if (scanf("%d", &N) != 1 || N < 1) {
        return 0;
    }

    long long totalSum = 0;  // общая сумма (будет собрана reduction-ом)

#pragma omp parallel num_threads(2) reduction(+ : totalSum)
    {
        int tid = omp_get_thread_num();  // номер нити: 0 или 1
        long long localSum = 0;          // частичная сумма для текущей нити

        if (tid == 0) {
            for (int i = 1; i <= N / 2; i++) {
                localSum += i;
            }
        } else {
            for (int i = (N / 2) + 1; i <= N; i++) {
                localSum += i;
            }
        }

        totalSum += localSum;

#pragma omp critical
        {
            printf("[%d]: Sum = %lld\n", tid, localSum);
        }
    }

    printf("Sum = %lld\n", totalSum);

    return 0;
}
