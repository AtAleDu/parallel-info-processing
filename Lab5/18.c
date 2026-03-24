#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int message;
    int prev = (rank - 1 + size) % size; // Номер соседа слева
    int next = (rank + 1) % size;        // Номер соседа справа

    if (rank == 0) {
        // Процесс 0 начинает эстафету
        message = rank; 
        // Отправляет следующему (1)
        MPI_Send(&message, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        
        // В самом конце ждет сообщение от последнего процесса (N-1)
        MPI_Recv(&message, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[%d]: receive message '%d'\n", rank, message);
    } 
    else {
        // Остальные сначала ЖДУТ сообщение от предыдущего
        MPI_Recv(&message, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[%d]: receive message '%d'\n", rank, message);
        
        // Увеличивают (инкрементируют) и передают дальше
        message++;
        MPI_Send(&message, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();// Почему после MPI_Finalize() нельзя использовать MPI функции? --- IGNORE ---
    return 0;
}