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
#include <sys/time.h>

//Se define la función MIN para obtener el valor minimo entre dos valores
#define MIN(x,y) ((x) < (y)) ? (x) : (y))



static struct timeval inicio,fin;  //Variables para medir el tiempo, globales


//Funcion para registar el tiempo inicial antes de ejecutar el algoritmo
void InicioMuestra(){
        gettimeofday(&inicio,NULL);
}


//Funcion para calcular y mostrar el tiempo que tarda en ejecutarse el algoritmo
void FinMuestra(){
        gettimeofday(&fin,NULL);
        fin.tv_usec -= inicio.tv_usec;
        fin.tv_sec -= inicio.tv_sec;
        double tiempo = (double) (fin.tv_sec * 1000000 + fin.tv_usec);
        printf("%9.0f \n", tiempo);


}

//Funcion para calcular la sumatoria de senos para un indice i
double fsum(int i){
        int j;
        int start = i * (i+1)/2;
        int finish = start + i;
        double return_val = 0;

        for(j = start; j < finish; j++)
                return_val += sin(j);

        return return_val;

}

/*
 * Función principal en la que:
 * El programa calcula la sumatoria de una función SENO en paralelo utilizando OpenMP.
 * El número de hilos y el número de repeticiones son ingresados por el usuario.
 * Se mide el tiempo de ejecución total del algoritmo para luego imprimirlo.
 */

int main (int argc, char *argv[]){
        double sum = 0;  //variable para almacenar la sumatoria de la función SENO

        //Verificacion de los argumentos de entrada
        if( argc != 3){
                printf("Error: \n\t$./ejecutable numHilos numRep\n");
                exit(0);
        }

        //Se reciben los argumentos de entrada
        int numHilos = (int) atoi(argv[1]);  //numero de hilos a utilizar
        int numRep = (int) atoi(argv[2]);    //numero de repeticiones para la sumatoria


        InicioMuestra();  //Se registra el tiempo inicial 

//Se ejecuta el algoritmo en paralelo
#pragma omp parallel
        {

        int threads = omp_get_num_threads();  //numero de hilos activos


#pragma omp master
        printf("Numero de Hilos: %d \n", threads);  //Hilo maestro imprime el numero de hilos

//Se realiza la paralelizacion del algoritmo
#pragma omp for reduction(+ : sum)
        for ( int i = 0; i <= numRep; i++){
                sum += fsum(i);  //Cada hilo calcula la sumatoria de la función SENO
        }
        }


        FinMuestra();  //Se calcula y muestra el tiempo que tarda en ejecutarse el algoritmo
        printf("La sumatoria de la función SENO: %.2f\n",sum);  //Se imprimen los resultados
        return 0;
}