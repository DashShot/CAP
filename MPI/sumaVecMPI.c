// cada proceso se encarga de sumar una parte del vector.
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int main(int argc, char** argv) {
    int rank, size, chunk_size;
    int i, sum = 0, local_sum = 0;
    int* vector;
    int* local_vector;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = N / size;

    vector = (int*) malloc(N * sizeof(int));
    local_vector = (int*) malloc(chunk_size * sizeof(int));

    if (rank == 0) {
        for (i = 0; i < N; i++) {
            vector[i] = i + 1;
        }
    }

    MPI_Scatter(vector, chunk_size, MPI_INT, local_vector, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    //El vector se divide en partes iguales y se distribuye a cada proceso utilizando la función MPI_Scatter(). 

    for (i = 0; i < chunk_size; i++) {
        local_sum += local_vector[i];
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    //la función MPI_Reduce() para reducir los resultados locales en una suma global en el proceso con rango 0

    if (rank == 0) {
        printf("La suma de los elementos del vector es: %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}
