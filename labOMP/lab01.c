/*
*	Autor: Juan Diego Rojas Osorio
*	Programa: hello.c
*	Fecha: 6 noviembre 2025
*	Tema: Programación Paralela- Introducción OpenMP
*	=========================================================
*	Resumen
*	Programa crea hilos de ejecución para cada core
*	imprime cadena de caracteres por cada llamada.
*
*/

#include <omp.h>		
#include <stdio.h>
#include <stdlib.h>

/*
 * Función principal en la que:
 * 1. Se obtiene el número máximo de hilos  disponibles en el SO.
 * 2. Se imprime el número total de cores en el SO detectados por OpenMP.
 * 3. Se crea una región paralela mediante la directiva #pragma omp parallel.
 * 4. Cada hilo dentro de la región paralela imprime su identificador único (ID).
 * 5. El programa finaliza.
 */

int main(int argc, char *argv[]){
  int maxCores = omp_get_max_threads();  //Numero maximo de cores del SO
  printf("Numero maximo de cores del SO: %d\n", maxCores);  //Se imprime el numero maximo de cores del SO
#pragma omp parallel
{	
  printf("Hello ID en region paralela: %d\n", omp_get_thread_num());  //Cada hilo imprime su identificador
}

  return 0;
}