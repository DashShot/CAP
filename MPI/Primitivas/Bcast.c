#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        data = 42;
    }

    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
//&data: Puntero al buffer de envío/recepción que contiene los datos a transmitir o recibir. En este caso, data es el puntero al dato que se va a transmitir o recibir.
// 1: Número de elementos que se transmiten o reciben. En este caso, se transmite o recibe un solo elemento.
// MPI_INT: Tipo de dato de los elementos que se transmiten o reciben. En este caso, el tipo de dato es MPI_INT, que representa un entero.
// 0: Rango del proceso raíz (el proceso que transmite los datos). En este caso, el proceso con rank 0 es el proceso raíz y es el encargado de transmitir los datos a los demás procesos.
// MPI_COMM_WORLD: Comunicador utilizado para la comunicación entre procesos. En este caso, se utiliza MPI_COMM_WORLD, que es el comunicador que representa a todos los procesos involucrados en la ejecución.
  
    printf("Process %d received data: %d\n", rank, data);

    MPI_Finalize();
    return 0;
}
