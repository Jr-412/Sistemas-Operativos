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
 * 1. Se declaran e inicializan las variables necesarias (contador, límites y valores iniciales)
 * 2. Se define una constante N que representa el número total de repeticiones
 * 3. Se inicializan las variables 'a' y 'b' con valores iniciales
 * 4. Se crea una región paralela con OpenMP usando la directiva 'parallel for'
 * 5. Se especifica que las variables 'i' y 'a' sean privadas para cada hilo
 * 6. Cada hilo ejecuta su parte del bucle calculando 'b = a + i'
 * 7. Una vez finalizada la región paralela, se imprime el valor esperado de 'a' y 'b'
 * 8. Se finaliza el programa 
 */

int main() {


    int i;
    const int N = 1000;  //Numero de repeticiones
    int a = 50;  
    int b = 0;

    // Región paralela con bucle for distribuido entre hilos, cada hilo tiene su propia copia de i y a
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++) {
        b = a + i;  
    }

    // Impresión de resultados fuera de la región paralela, muestra el valor esperado para a y para b
    printf("a = %d  b = %d (Se espera a = 50, b = 1049)\n", a, b);

    return 0;
}