#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    
    int rank, size, n, result = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    //inicializa el entorno MPI. Recibe dos parámetros: "argc" y "argv", que se pasan al programa principal y se utilizan para inicializar el entorno MPI.
    
    /*MPI_COMM_WORLD es un comunicador predefinido en MPI 
     que se utiliza para representar el conjunto completo de procesos que se están ejecutando en el programa MPI. 
     Este comunicador se crea automáticamente cuando se inicializa el entorno MPI 
     y contiene todos los procesos que están en ejecución en el momento de la llamada a MPI_Init().*/
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    /*esta función obtiene el identificador (rango) del proceso actual en el comunicador global MPI_COMM_WORLD.
    Recibe dos parámetros: el comunicador global MPI_COMM_WORLD 
    y un puntero a una variable de entero "rank" que se utiliza para almacenar el rango del proceso actual.*/
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /*esta función obtiene el número total de procesos que están en el comunicador global MPI_COMM_WORLD.
    Recibe dos parámetros: el comunicador global MPI_COMM_WORLD 
    y un puntero a una variable de entero "size" que se utiliza para almacenar el número total de procesos.*/


    // El proceso maestro envía tareas a los procesos esclavos
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            /*esta función envía datos desde un proceso a otro proceso en el comunicador MPI_COMM_WORLD.
             Recibe seis parámetros: un puntero al buffer que contiene los datos, el número de elementos que se enviarán (en este caso, 1), 
             el tipo de datos que se enviarán (MPI_INT), el rango del proceso destinatario (en este caso, "i"), una etiqueta (en este caso, 0)
             y el comunicador MPI_COMM_WORLD.*/
        }
    }

    // Los procesos esclavos reciben tareas y envían resultados de vuelta al maestro
    if (rank > 0) {
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        /*esta función recibe datos de otro proceso en el comunicador MPI_COMM_WORLD.
         Recibe siete parámetros: un puntero al buffer donde se almacenarán los datos recibidos,
         el número de elementos que se recibirán (en este caso, 1), el tipo de datos que se recibirán (MPI_INT), 
         el rango del proceso remitente (en este caso, 0), una etiqueta (en este caso, 0), el comunicador MPI_COMM_WORLD y 
         un objeto de estado MPI_Status que se utiliza para almacenar información sobre la comunicación.*/
        for (int i = 1; i <= n; i++) {
            result += i;
        }
        MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // El proceso maestro recopila y combina los resultados de los procesos esclavos
    if (rank == 0) {
        int final_result = 0;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&result, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            final_result += result;
        }
        cout << "La suma total es: " << final_result << endl;
    }

    MPI_Finalize();
    //esta función finaliza el entorno MPI. No recibe parámetros.
    return 0;
}
