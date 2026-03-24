#include <stdio.h>
#include <omp.h>
//в чем отличие
int main(void) {
    omp_set_num_threads(20);
    #pragma omp parallel
    {   
        printf("Hello World!\n");
    }
    #pragma omp parallel num_threads(10)
    {
        printf("Hello World dsfgdsf!\n");
    }
    #pragma omp parallel
    {   
        printf("Hello Wвввввorld!\n");
    }
}
