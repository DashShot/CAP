#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#include<omp.h>

int max(int *array, int size){ //Función máximo
    int max = array[0];
    /* 
    #pragma omp parallel //directiva de parelización
    {
        int local_max = array[0]; //cada hilo almacena su maximo local

        #pragma omp for
        for (int i = 1;i < size ; i++){
            if (array[i] > local_max){
                local_max = array[i];
            }
        }
        #pragma omp critical //solo un hilo a la vez actualiza max
        {
            if(local_max > max){
                max = local_max;
            }
        }

    } 
    return max;
    */
   int num_threads = omp_get_max_threads();

   for (int stride = size/2 ; stride > 0 ; stride /= 2){//En este bucle externo vamos reduciendo gradualmente el arreglo
        #pragma omp parallel for num_threads(num_threads)
        for (int i = 0; i < stride ; i++){
            int index = i *2;
            if (array[index] < array[index+1]){
                array[index] = array[index + 1];
            }
        }
   }
   return array[0];
}

void countSort(int* array, int size) { //Algoritmo CountSort
    int* count = (int*)calloc(10000, sizeof(int)); // Inicializamos el array secundario a cero
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        #pragma omp atomic //garantiza la actualización segura del contador count
        count[array[i]]++;// Sumamos uno en cada posición del array secundario en la posición que corresponda al valor leído
    }
    int index = 0;
    #pragma omp parallel for
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < count[i]; j++) {// Escribimos en el array inicial los valores ordenados
            #pragma omp atomic    
                array[index++] = i;
        }
    }
    free(count);
}

double get_wall_time()//Medir el tiempo de ejecución en segundos
{
    struct timeval time;
    if (gettimeofday(&time, NULL) == 0)
    {
        return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
    }
    else
    {
        return 0.0;
    }
}

int main()
{
    int N = 1000000; // Tamaño del arreglo
    
    // Crear un arreglo de enteros de tamaño N con valores aleatorios
    int* array = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % 10000; // Valores aleatorios entre 0 y 9999
    }
    
    // Probar countSort y medir su tiempo de ejecución
    double start_time = get_wall_time();
    countSort(array, N);
    double end_time = get_wall_time();
    double countSort_execution_time = end_time - start_time;
    
    // Imprimir el arreglo ordenado después de countSort 
    /*
    printf("Arreglo ordenado después de countSort:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    */
    
    // Probar max y medir su tiempo de ejecución
    start_time = get_wall_time();
    int max_value = max(array, N);
    end_time = get_wall_time();
    double max_execution_time = end_time - start_time;
    
    printf("El valor máximo es: %d\n", max_value);
    printf("Tiempo de ejecución de countSort: %f segundos\n", countSort_execution_time);
    printf("Tiempo de ejecución de max: %f segundos\n", max_execution_time);
    
    // Liberar la memoria del arreglo
    free(array);
    
    return 0;
}
