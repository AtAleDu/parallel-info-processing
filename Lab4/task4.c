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


/*
8) Продемонстрируйте конфликт обращений к переменной rank в задании №4?
 Всегда ли он возникает? Как его предотвратить? 
#include <stdio.h>
#include <omp.h>

int main() {
    int k = 4;
    int rank;

#pragma omp parallel num_threads(k)
    {
        rank = omp_get_thread_num();
        printf("I am %d thread\n", rank);
    }

    return 0;
}
*/