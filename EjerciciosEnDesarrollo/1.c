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
#include<stdlib.h>
#include<time.h>
#include<omp.h>

int main (int argc, char *argv[]){

    if(argc == 2){

        int N = atoi(argv[1]);

        int vA[N];
        int vB[N];

        double t0,t1;

        srand(time(NULL)); //semilla de aleatoriedad

        for (int i=0 ; i<N ; i++){ //LLenado de arrays
            vA[i] = rand()%1000;
            vB[i] = rand()%1000;
        }
        printf("Valores iniciales vA = ");
        for(int i1 = 0 ; i1<N ; i1++) printf ("%d ", vA[i1]);
        printf("\nValores iniciales vB = ");
        for(int i2 = 0 ; i2<N ; i2++) printf ("%d ", vB[i2]);
        
         t0=omp_get_wtime();

        #pragma omp parallel for num_threads(4)
        for(int j=0 ; j<N ; j++){ //Suma almacenada en vA
            vA[j] +=vB[j];
        }

        t1=omp_get_wtime();

        printf("\nValor final de vA =  ");
        for(int i3 = 0 ; i3<N ; i3++) printf ("%d ", vA[i3]);


        printf("\n%f,- %f\n",t0,t1);
        double elapsed = t1-t0;

        printf("\nEl tiempo transcurrdo es = %f",elapsed);
        
    }else{ //TRATAMIENTO DE PARAMETROS
        printf("EL NUMERO DE ARGOMENTOS NO ES CORRECTO \n");
        return -1;
    }
} 