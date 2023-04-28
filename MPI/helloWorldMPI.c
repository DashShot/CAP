#include <mpi.h>
#include<stdio.h>

int main (int argc, char** argv[]){

    //Inicializar el entorno MPI
    MPI_Init(NULL,NULL);

    //Get number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //Get rank of process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);

    //Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name,&name_len);

    //print hello world messsage
    printf("Hello world from processor %s , rank %d out of %d processors\n",processor_name, world_rank, world_size);

    //Finalizar el entorno MPI
    MPI_Finalize();   

}
/* 
La función MPI_Init() se utiliza para inicializar el entorno MPI y la función MPI_Finalize() para finalizarlo.
La función MPI_Comm_rank() devuelve el rango (rank) del proceso actual y MPI_Comm_size() devuelve el número total de procesos que se están ejecutando.
*/