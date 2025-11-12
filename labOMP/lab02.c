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


/*
 * Función principal en la que:
 * 1. Se verifica que el usuario ingrese el número correcto de argumentos (cantidad de hilos).
 * 2. Se convierte el argumento recibido a un entero (numHilos).
 * 3. Se obtiene el número máximo de hilos soportados por el SO.
 * 4. Se imprime información sobre los cores disponibles en el procesador y el número de hilos deseados.
 * 5. Se configura el número de hilos que OpenMP utilizará en las regiones paralelas.
 * 6. Se ejecuta una región paralela donde cada hilo imprime su identificador.
 * 7. Finaliza el programa.
 */

int main(int argc, char *argv[]){
  
  //Verificación de los argumentos de entrada
  if (argc != 2){
    printf("Error: \n\t$ ./ejecutable numHilos\n");
    exit(0);
  }

  int numHilos = (int) atoi(argv[1]);  //Numero de hilos a utilizar

  int maxCores = omp_get_max_threads();  //Numero maximo de cores del SO
  printf("Número máximo de Cores del SO: %d \n", maxCores);  //Se imprime el numero maximo de cores del SO
  printf("Número de hilos deseado: numHilos\n");
 
  /*Se fija el número de hilos deseado: numHilos*/
  omp_set_num_threads(numHilos);
  printf("Número hilos fijados: %d \n", numHilos);

  /*Región Paralela por OMP*/
  #pragma omp parallel
  {
    printf("Hilo ID en Región Paralela: %d \n", omp_get_thread_num());  //Cada hilo imprime su identificador
  }

  return 0;
}