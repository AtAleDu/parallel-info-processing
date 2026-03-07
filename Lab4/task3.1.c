#include <stdio.h>
#include <omp.h>

int main(void) {
    int k = 0; 
    printf("Enter the number of threads: ");
    if (scanf("%d", &k) != 1 || k <= 0) {
        return 0; 
    }

#pragma omp parallel num_threads(k)
    {
        int rank = omp_get_thread_num();// номер текущей нити

        int total = omp_get_num_threads();// общее число нитей

#pragma omp critical
        {
            printf("I am %d thread from %d threads!\n", rank, total);
        }
    }

    return 0;
}
