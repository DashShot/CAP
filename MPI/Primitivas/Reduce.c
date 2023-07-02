#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, local_value, global_sum;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_value = rank + 1;

    MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

// &local_value: Puntero al buffer de envío que contiene los datos locales que se van a reducir. En este caso, local_value es el puntero al dato local que se va a reducir.
// &global_sum: Puntero al buffer de recepción que almacena el resultado de la operación de reducción. En este caso, global_sum es el puntero al dato que almacenará el resultado de la reducción.
// 1: Número de elementos que se envían en el buffer de envío y se reciben en el buffer de recepción. En este caso, se envía y recibe un solo elemento.
// MPI_INT: Tipo de dato de los elementos que se envían y reciben. En este caso, el tipo de dato es MPI_INT, que representa un entero.
// MPI_SUM: Operación de reducción que se realizará sobre los datos. En este caso, se realiza una suma de los datos.
// 0: Rango del proceso raíz (el proceso que recibe el resultado de la reducción). En este caso, el proceso con rank 0 es el proceso raíz y es el que recibirá el resultado de la reducción.
// MPI_COMM_WORLD: Comunicador utilizado para la comunicación entre procesos. En este caso, se utiliza MPI_COMM_WORLD, que es el comunicador que representa a todos los procesos involucrados en la ejecución.

    if (rank == 0) {
        printf("Global sum: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
// MPI_MAX: Realiza una reducción tomando el máximo valor entre los datos.
// MPI_MIN: Realiza una reducción tomando el mínimo valor entre los datos.
// MPI_PROD: Realiza una reducción multiplicando los valores entre los datos.
// MPI_LAND: Realiza una reducción lógica AND entre los valores booleanos de los datos.
// MPI_BAND: Realiza una reducción bit a bit AND entre los valores enteros de los datos.
// MPI_LOR: Realiza una reducción lógica OR entre los valores booleanos de los datos.
// MPI_BOR: Realiza una reducción bit a bit OR entre los valores enteros de los datos.
// MPI_LXOR: Realiza una reducción lógica XOR entre los valores booleanos de los datos.
// MPI_BXOR: Realiza una reducción bit a bit XOR entre los valores enteros de los datos