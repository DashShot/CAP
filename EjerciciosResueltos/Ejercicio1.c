#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

//Ejercicio 1
//Alumno: Aitor Garcia Camargo
int main(int argc, char **argv){
    //Declaramos dos arrays
    int *array1;
    int *array2;
    //int n = argv[1];
    int n ;
    printf("Introduzca el valor de tamano del array\n");
    scanf("%d",&n);
    //Reservamos el espacio en memoria dinamiaca necesaria con la variable n pedida anteriormente
    array1 = (int*) malloc(n*sizeof(int));
    array2 = (int*) malloc(n*sizeof(int));
    srand(0);
    //Rellenamos los array por medio de valores entre 1-10000
    for(int i = 0; i<n;i++){
        array1[i] = rand() %10000;
        array2[i] = rand() %10000;

    }
    //Bucle para ver los valores que se encuentran en los arrays
    /*for(int i = 0; i <n; i++){
        printf("Array 1 posicion %d, valor %d\n",i,array1[i]);
        printf("Array 2 posicion %d, valor %d\n",i,array2[i]);

    }
     */
    //Seteamos en inicio del tiempo
    time_t t0 = clock();
    #pragma omp parallel for num_threads(4)
    //num_threads(4) --> realiza la ejecucion igual para cada una de los hilos
    //pragma omp -> dividirá el for en subprocesos
    //Suma de los dos arrays y se almacenaran en el array 1
    for(int i = 0; i<n;i++){
        array1[i] = array1[i]+array2[i];

    }
    //Finalizamos el tiempo que ha tardado en realizar la suma
    time_t t1 = clock();
    double elipse = (double)(t1-t0)/CLOCKS_PER_SEC;
    printf("Tiempo = %f",elipse);
    /*for(int i = 0; i <n; i++){
        printf("Array Suma posicion %d, valor %d\n",i,array1[i]);

    }
     */
    //Liberamos el espacio del array 1, como del array2
    free(array1);
    free(array2);
    return 0;
}

/*
  -Al usar el calculo de tiempo, podemos comprobar que el programa tras la ejecución tardará ->0.28 segundos con una entradas de 
datos de 100.000 datos
  -Al incluir "#pragma"--> nueestro programa tendrá un tiempo de 0.26 segundos en la ejecución con la misma entrada de datos, esto 
es debido a introducir dicha linea de código
  
*/