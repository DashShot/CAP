#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

/*
Caso base 1 -> si tiene un elemento. lo deja igual
Caso base 2 -> si el tiene dos elementos
 -Si el primero es menor o igual, nada
 -Si el primero es mayor, cambio
Caso general:
 -Elegir el pivote -> 2 primeras filas -> primer elemento
 -Crear array del mismo tamaño qu eel original
 -Crar array del mimso tamaño que el original
 -Recorrero el array y colocar los valroes menores que el pivote al inicio
 -Contamos los valores menores
 -Los valores mayores igual, pero se colocan desde el final hacia atras y los contamos
 -Los valores que sean iguales simplemente los contamos
 -Pisamos los valores de nuestro array original con los nuevos
 -Nos cargamos el array temporal que hemos generado
*/
void OrdenarQuickSort(int *array,int size){
    if (size <=1){
        return;
    }else if(size == 2){
        //Comprobamos si en el arrayhay dos valores y si esta ordenados
        if(array[0]<=array[1]){
            return;
        }else{
            int aux = array[0];
            array[0]= array[1];
            array[1]= aux;
        }
    }else {
        int pivote = array[0];
        int *arrayAux = (int *) malloc(size * sizeof(int));;
        int menores = 0;
        int mayores = size -1;
        int iguales = 1;
        //Realizamos un bucle para comprobar si los valores del array son mayores menors o iguales que el pivote
        for (int i = 0; i < size; i++) {
            if  (array[i]<pivote) {
                arrayAux[menores++] = array[i];
            } else if (array[i]==pivote){
                iguales ++;
            }else{
                arrayAux[mayores--] = array[i];
            }
        }
        //Introducimos en el array los valores iguales al pivote
        for(int j = menores; j<=mayores;j++){
            arrayAux[j] = pivote;
        }
        //copiamos el array auxiliar al array normal
        memcpy( array, arrayAux, size*sizeof(int));
        //Liberamos el array auxiliar
        free(arrayAux);
        //llamada recursiva para ordenar los valores menores del array
        OrdenarQuickSort(array, menores);
        //llamada recursiva para ordenar los valores mayores del array
        OrdenarQuickSort(array+menores+iguales, size-menores-iguales);

    }
}

int main(int argc, char *argv[]){
    int *array1;
    int n = atoi(argv[1]);

    //printf("Introduzca el valor de tamano del array\n");
    //scanf("%d",&n);
    array1 = (int*) malloc(n*sizeof(int));
    srand(0);
    for(int i = 0; i<n;i++){
        array1[i] = rand() %9999;

    }
    //Array sin ordenar
    printf("Array sin ordenar:");
    for(int i = 0; i<n;i++){
        printf(" [%d]",array1[i]);

    }
    printf("\n-----------------\n");
    //Ordenamos el array
    OrdenarQuickSort(array1,n);
    //Imprimo el array ordenado
    printf("Array ordenado:");
    for(int i = 0; i<n;i++){
        printf(" [%d]",array1[i]);

    }
    free(array1);


}