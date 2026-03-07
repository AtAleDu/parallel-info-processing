#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel num_threads(4)
    {
#pragma omp critical
        {
            printf("Hello World!\n");
        }
    }

    return 0;
}
