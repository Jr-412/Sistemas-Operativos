/****************************************************
* Pontificia Universidad Javeriana
* Docente: J. Corredor
* Autor: Juan Diego Rojas Osorio
* Fecha: 23/10/2025
* Materia: Sistemas Operativos
****************************************************/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

//Número total de hilos que se van a crear (en este caso, 10)
#define NTHREADS 10
//Declaración e inicialización del mutex para controlar el acceso concurrente
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

//Función que será ejecutada por cada hilo
void *thread_function(void *arg) {
    int i = *(int *)(arg);
    //Muestra el número del hilo junto con su identificador
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());
    //Bloquea el mutex para que solo un hilo modifique el contador a la vez
    pthread_mutex_lock(&mutex1);
    counter++;
    //Desbloquea el mutex para permitir que otros hilos puedan acceder al contador
    pthread_mutex_unlock(&mutex1);
}

void main() {

    //Arreglo donde se almacenan los identificadores de cada hilo creado
    pthread_t thread_id[NTHREADS];
    int i, j;
    //Bucle que crea los 10 hilos; cada uno trabaja de forma independiente, pero con exclusión mutua
    for(i = 0; i < NTHREADS; i++) {
        pthread_create(&thread_id[i], NULL, thread_function, &i);
    }

    //Bucle que espera a que todos los hilos terminen antes de continuar
    for(j = 0; j < NTHREADS; j++) {
        pthread_join(thread_id[j], NULL);
    }

    //Muestra el valor total del contador una vez que todos los hilos han finalizado
    printf("Final counter value: %d\n", counter);
}
