/*
*	Autor: Juan Diego Rojas Osorio
*	Materia: Sistemas Operativos
*	Tema: introducción a OPENMP
*	Descripción:
*		- Uso de la directiva y función para hacer uso de OpenMP
*	*******************
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Función principal en la que:
 * 1. Se definen las variables necesarias para el bucle paralelo.
 * 2. Se establece el numero de repeticiones, en este caso 1000, y los valores iniciales de las variables a y b.
 * 3. Se ejecuta un bucle paralelo con OpenMP donde se declara 'i', 'a' y 'b' como variables privadas.
 * 4. Cada hilo trabaja con sus propias copias de las variables, con el fin de evitar condiciones de carrera.
 * 5. Se imprime el valor final de las variables 'a' y 'b' después de la región paralela.
 * 6. Se finaliza la ejecución del programa.
 */
int main() {
    int i;
    const int N = 1000;  //Numero de repeticiones
    int a = 50;
    int b = 0;

    // Región paralela con bucle for distribuido entre hilos, cada hilo tiene su propia copia de i, a y b
    #pragma omp parallel for private(i) private(a) private(b)
    for (i = 0; i < N; i++) {
        b = a + i;  // Cada hilo calcula b = a + i
    }

    // Impresión de resultados fuera de la región paralela, muestra el valor esperado para a y para b, esta vez las copias de a y b no se comparten 
    printf("a = %d  b = %d (Se espera a = 50, b = 1049)\n", a, b);

    return 0;
}