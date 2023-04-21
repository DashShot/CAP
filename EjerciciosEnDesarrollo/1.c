/* 
    Aplicación en C que recibe un único argumento N al ejecutarse, crear dos arrays que se
    de tamaño N, vA y vB que se rellenen con aleatorios del 1-1000. 
    Hacer vA[i]+=vB[i] y medir el tiempo que tarda e imprimir por pantalla.

    Compilar:
        1º- Sin opciones adicionales -> gcc 1.c -o 1
        2º- Añadiendo -O1 -O2 y sus nuevos tiempos 

    OpenMP


*/
#include<stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

    if(argc == 2){

        int N = argv[1];

        int vA[N];
        int vB[N];

        srand(time(NULL)); //semilla de aleatoriedad

        for (int i=0 ; i<N ; i++){ //LLenado de arrays
            vA[i] = rand()%1000;
            vB[i] = rand()%1000;
        }
        printf("Valores iniciales vA = %i \n",vA);
        printf("Valores iniciales vB = %i \n",vB);

        for(int j=0 ; j<N ; j++){ //Suma almacenada en vA
            vA[j] +=vB[j];
        }

        printf("Valor final de vA = %i \n",vA);



    }else{ //TRATAMIENTO DE PARAMETROS
        printf("EL NUMERO DE ARGOMENTOS NO ES CORRECTO \n");
        return -1;
    }
} 