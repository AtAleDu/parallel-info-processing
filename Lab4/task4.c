#include <stdio.h>
#include <omp.h>

int main(void) {
    int k = 0;

    if (scanf("%d", &k) != 1 || k <= 0) {
        return 0;
    }

#pragma omp parallel num_threads(k)
    {
        int rank = omp_get_thread_num();  

#pragma omp critical
        {
            printf("I am %d thread.\n", rank);
        }
    }

    return 0;
}
