/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Autor: Juan Diego Rojas Osorio
 *        Juan José Ballesteros
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 27/10/2025
 * Tema: Posix para la creación de hilos concurrentes:
 *
 * Descripción:
 * "
 *    Este programa implementa la parte consumidora del problema productor-consumidor, en este se hace uso memoria compartida y semáforos POSIX 
 *    para sincronizar dos procesos distintos.
 * "
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "maximo.h"

int main(int argc, char *argv[]) {
        FILE *fichero;  //Puntero al archivo donde se leen los datos
        int n, nhilos, i;  //tamano del vector y el numero de hilos, respectivamente
        int *vec;  //puntero al vector de enteros
        int ret, maximo;  //variable para verificar la lectura del archivo y el maximo valor encontrado, respectivamente

        //Se verifica que se ingresen los argumentos correctos
        if (argc!=3) {
                fprintf(stderr, "Error en número de argumentos \n");
                exit(-1);
        }
        //Se abre el archivo 
        fichero = fopen(argv[1], "r");
        //Se verifica si se abrio correctamente el archivo
        if (fichero == NULL) {
                perror("No se puede abrir fichero");
                exit(-2);
        }

        //Lee el tamano del vector
        ret = fscanf(fichero, "%d", &n);
        if (ret !=1) {
                fprintf(stderr, "No se puede leer tamaño\n");
                exit(-3);
        }
        nhilos = atoi(argv[2]);  //Cantidad de hilos

        //Se reserva memoria para el vector
        vec = malloc(sizeof(int) * n);

        //Se leen lo valores del vector desde el archivo
        for (i=0;i!=n;++i) {
                ret = fscanf(fichero, "%d", &vec[i]);
                if (ret !=1) {
                        fprintf(stderr, "No se puede leer elemento nro %d\n", i);
                        fclose(fichero);
                        free(vec);
                }
        }
        maximo = maximoValor(vec,n,nhilos); //Se busca el maximo valor en el vector
        printf("Máximo: %d\n", maximo);  //Se imprime el maximo valor del vector
        fclose(fichero);  //Cierra el archivo
        free(vec);  //Libera memoria
        return 0;
}

