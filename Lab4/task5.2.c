#include <stdio.h>
#include <omp.h>

int main(void) {
    int k = 0;
    int N = 0;
    printf("Enter the number of threads: ");
    if (scanf("%d", &k) != 1 || k <= 0) {
        return 0;
    }
    printf("Enter N: ");
    if (scanf("%d", &N) != 1 || N < 1) {
        return 0;
    }

    long long totalSum = 0;

#pragma omp parallel num_threads(k) reduction(+ : totalSum)
    {
        int tid = omp_get_thread_num();            // номер нити [0..k-1]
        int totalThreads = omp_get_num_threads();  // фактическое число нитей
        long long localSum = 0;

        int block = N / totalThreads;
        int rem = N % totalThreads;
        int start = 0;
        int end = 0;

        if (tid < rem) {
            start = tid * (block + 1) + 1;
            end = start + (block + 1) - 1;
        } else {
            start = rem * (block + 1) + (tid - rem) * block + 1;
            end = start + block - 1;
        }

        if (start <= N && start <= end) {
            if (end > N) {
                end = N;
            }
            for (int i = start; i <= end; i++) {
                localSum += i;
            }
        } else {
            localSum = 0;  // если нитей больше, чем чисел, то некоторые нити ничего не суммируют
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
