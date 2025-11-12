/*
*	Autor: Juan Diego Rojas Osorio
*	Materia: Sistemas Operativos
*	Tema: introducción a OPENMP
*	Descripción:
*		- Uso de la directiva y función para hacer uso de OpenMP
*	*******************
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
//Se define la función MIN para obtener el valor minimo entre dos valores
#define MIN(x,y) ((x) < (y)) ? (x) : (y)) 


//Funcion para calcular la sumatoria de senos para un indice i
double fsum(int i){
        int j, start = i * (i+1)/2, finish = start + i;  //calcula el rango de la sumatoria
        double return_val = 0;
        for(j = start; j < finish; j++)
                return_val += sin(j);

        return return_val;  //retorna el valor de la sumatoria

}

/*
 * Función principal en la que:
 * El programa calcula la sumatoria de una función SENO en paralelo utilizando OpenMP. 
 *El número de hilos es ingresado como argumento.
 *Se emplea una directiva 'reduction' para combinar las sumas parciales realizadas por cada hilo de forma segura.
 */

int main (int argc, char *argv[]){
        double sum = 0;   //variable para almacenar la sumatoria de la función SENO
        int rep = 30000;  //Numero de repeticiones para la sumatoria

        //Verificacion de los argumentos de entrada
        if( argc != 2){
                printf("Error: \n\t$./ejecutable numHilos\n");
                exit(0);
        }
        
        int numHilos = (int) atoi(argv[1]);  //numero de hilos a utilizar

#pragma omp parallel
        {
        int threads = omp_get_num_threads();   //numero de hilos activos
#pragma omp master
        printf("Numero de Hilos: %d \n", threads);   //Hilo maestro imprime el numero de hilos

//Se realiza la paralelizacion del algoritmo
#pragma omp for reduction(+ : sum)
        for ( int i = 0; i <= rep; i++){
                sum += fsum(i);
        }
        }

        printf("La sumatoria de la función SENO: %.2f\n", sum);  //Se imprimen los resultados
        return 0;
}