//Aitor García Camargo
#include <stdio.h>   // Biblioteca estándar de C
#include <stdlib.h>  // Para la función malloc y rand
#include <time.h>    // Para inicializar la semilla del generador de números aleatorios

#include <mpi.h>

#define NUM_TAREAS 100

int foo (int  task, double **result){
    int i;
    int size = rand()%task; //tamaño de los resultados

    (*result) = (double*)malloc(size*sizeof(double)); //resultados por parámetro
    for (i = 0 ; i < size ; i++){
        (*result)[i] = (double)rand()/RAND_MAX;
    }
    return size;
} 

int main(int argc, char **argv){

    int hayTrabajo = 1;
    int rank, size;


    int tareas[NUM_TAREAS];
    int tareaIndex = 0;

    double *resultado;
    int resultado_size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){ //maestro
            for (int j = 0 ; j < NUM_TAREAS ; j++){//Generar tareas a los esclavos
                tareas[j] = rand()%100;
            }            
            int i; 
            MPI_Request *estadoNodos = (MPI_Request *)malloc(sizeof(MPI_Request)*size); //crea un array de objetos MPI_Request, para almacenar los identificadores de las solicitudes de comunicación
            
            for (i = 1 ; i < size ; i++ ){ // Envia tareas a los esclavos
               if (tareaIndex <= NUM_TAREAS){
                    MPI_Send(&hayTrabajo, 1 , MPI_INT, i, 1,MPI_COMM_WORLD);
                    MPI_Send(&tareas[tareaIndex],1,MPI_INT,i,0,MPI_COMM_WORLD);
                    tareaIndex++;             
               }else{
                    hayTrabajo = 0;
                    MPI_Send(&hayTrabajo, 1 , MPI_INT, i, 1,MPI_COMM_WORLD);
               }
            }

            while (1){
                for ( i = 1 ; i < size ; i++){
                    if (MPI_Request_get_status(estadoNodos[i],0,MPI_STATUS_IGNORE)){//verifica si una solicitud de comunicación ha sido completada
                        if (tareaIndex > 99){
                            hayTrabajo = 0;
                        }
                        //Recibit resultados y calcular media
                        MPI_Irecv(&resultado_size,1,MPI_INT,i,0,MPI_COMM_WORLD,&estadoNodos[i]);
                        if (resultado_size > 0){
                            resultado = (double *)malloc(resultado_size * sizeof(double));
                            MPI_Recv(&resultado,resultado_size,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

                            double suma;
                            for (int k = 0 ; k < resultado_size; k++){
                                suma += resultado[k];
                            }
                            double media = suma / resultado_size;
                            printf("Media = %f \n",media);

                        }
                        MPI_Send(&hayTrabajo, 1 , MPI_INT, i, 1,MPI_COMM_WORLD); // Enviar nuevas tareas
                        if(hayTrabajo){
                            MPI_Send(&tareas[tareaIndex],1,MPI_INT,i,0,MPI_COMM_WORLD);
                            tareaIndex++;
                            MPI_Irecv(&resultado,1,MPI_INT,i,0,MPI_COMM_WORLD,&estadoNodos[i]);                            
                        }
                    }
                }
            }
            free(estadoNodos);
            
    }else{ //esclavos
        while (1){
            MPI_Recv(&hayTrabajo,1,MPI_INT, 0 , 1 , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if(!hayTrabajo){
                break;
            }
            MPI_Recv(&tareas[tareaIndex],1,MPI_INT,0,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            resultado_size = foo(tareas[tareaIndex],&resultado);
            MPI_Send(&resultado_size,1,MPI_INT,0,0,MPI_COMM_WORLD);
            MPI_Send(&resultado,resultado_size,MPI_DOUBLE,0,0,MPI_COMM_WORLD);

            free(resultado);
        }

        MPI_Finalize();
        return 0;
        
    }

}