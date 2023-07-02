#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int sendbuf[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    int recvbuf[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(sendbuf, 2, MPI_INT, recvbuf, 2, MPI_INT, 0, MPI_COMM_WORLD);
    
// sendbuf: Puntero al buffer de envío que contiene los datos a distribuir. En este caso, sendbuf es un puntero al arreglo sendbuf en el proceso con rank 0.
// 2: Número de elementos que se envían a cada proceso. En este caso, se envían 2 elementos a cada proceso.
// MPI_INT: Tipo de dato de los elementos que se envían.
// recvbuf: Puntero al buffer de recepción que almacena los datos recibidos por cada proceso. En este caso, recvbuf es un puntero al arreglo recvbuf específico para cada proceso.
// 2: Número de elementos que se reciben en cada proceso. En este caso, se reciben 2 elementos.
// MPI_INT: Tipo de dato de los elementos que se reciben.
// 0: Rango del proceso raíz (el proceso que envía los datos). En este caso, el proceso con rank 0 es el proceso raíz.
// MPI_COMM_WORLD: Comunicador utilizado para la comunicación entre procesos.

    printf("Process %d received data: %d %d\n", rank, recvbuf[0], recvbuf[1]);

    MPI_Gather(recvbuf, 2, MPI_INT, sendbuf, 2, MPI_INT, 0, MPI_COMM_WORLD);

// recvbuf: Puntero al buffer de envío que contiene los datos a enviar al proceso raíz. En este caso, recvbuf es un puntero al arreglo recvbuf específico para cada proceso.
// 2: Número de elementos que se envían desde cada proceso. En este caso, se envían 2 elementos desde cada proceso.
// MPI_INT: Tipo de dato de los elementos que se envían.
// sendbuf: Puntero al buffer de recepción en el proceso raíz que recopila los datos de todos los procesos. En este caso, sendbuf es un puntero al arreglo sendbuf en el proceso con rank 0.
// 2: Número de elementos que se reciben en el proceso raíz desde cada proceso. En este caso, se reciben 2 elementos desde cada proceso.
// MPI_INT: Tipo de dato de los elementos que se reciben.
// 0: Rango del proceso raíz (el proceso que recopila los datos). En este caso, el proceso con rank 0 es el proceso raíz.
// MPI_COMM_WORLD: Comunicador utilizado para la comunicación entre procesos.

    if (rank == 0) {
        printf("Gathered data: ");
        for (int i = 0; i < 8; i++) {
            printf("%d ", sendbuf[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
