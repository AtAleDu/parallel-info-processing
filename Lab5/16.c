#include <stdio.h>
#include <mpi.h>
#include <omp.h> // 1. Подключаем заголовок OpenMP

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    omp_set_num_threads(4);

    if (rank == 0) {
        printf("Master MPI process 0 sees %d total processes.\n", size);
    }

    // Создаем параллельный регион OpenMP внутри каждого процесса
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        
        // Логика вывода
        if (rank == 0) {
            printf("  [Process %d] Thread %d is reporting for duty!\n", rank, thread_id);
        } else {
            const char* team = (rank % 2 != 0) ? "FIRST" : "SECOND";
            printf("  [Process %d] Thread %d says: I am %s!\n", rank, thread_id, team);
        }
    }

    MPI_Finalize();
        MPI_Init(&argc, &argv);

    int size1, rank1;
    MPI_Comm_size(MPI_COMM_WORLD, &size1);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank1);

    omp_set_num_threads(4);

    if (rank == 0) {
        printf("Master MPI process 0 sees %d total processes.\n", size1);
    }

    // Создаем параллельный регион OpenMP внутри каждого процесса
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        
        // Логика вывода
        if (rank == 0) {
            printf("  [Process %d] Thread %d is reporting for duty!\n", rank1, thread_id);
        } else {
            const char* team = (rank % 2 != 0) ? "FIRST" : "SECOND";
            printf("  [Process %d] Thread %d says: I am %s!\n", rank1, thread_id, team);
        }
    }

    MPI_Finalize();
    return 0;
}