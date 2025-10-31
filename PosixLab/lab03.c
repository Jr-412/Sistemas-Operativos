/**********************************************
* Pontificia Universidad Javeriana
* Autor: Juan Diego Rojas Osorio
* Fecha: Octubre 30 2025
* Materia: Sistemas Operativos
* Tema: Threads
*  
* **********************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Inicialización de los mutex y la variable de condición
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

//Variable compartida entre los hilos
int count = 0;

//Constantes que definen los límites de la cuenta
#define COUNT_DONE  15
#define COUNT_HALT1 4
#define COUNT_HALT2 11

//Función ejecutada por el primer hilo
void *count01() {
    for (;;) {
        //Bloquea el mutex de condición para verificar los rangos
        pthread_mutex_lock(&condition_mutex);
        //Si el contador está dentro del rango de pausa, el hilo espera
        while (count >= COUNT_HALT1 && count <= COUNT_HALT2)
        {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);

        //Incrementa el contador de manera segura
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 01 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        //Finaliza el hilo cuando se alcanza el valor máximo
        if (count >= COUNT_DONE) return(NULL);
    }
}

//Función ejecutada por el segundo hilo
void *count02() {
    for (;;) {

        //Bloquea el mutex de condición para controlar la señal
        pthread_mutex_lock(&condition_mutex);
        //Envía una señal cuando el contador está fuera del rango de pausa
        if (count < COUNT_HALT1 || count > COUNT_HALT2)
        {
            pthread_cond_signal(&condition_cond);
        }
        pthread_mutex_unlock(&condition_mutex);

        //Incrementa el contador de manera segura
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 02 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        //Finaliza el hilo cuando se alcanza el valor máximo
        if (count >= COUNT_DONE) return(NULL);
    }
}

void main() {

    //Declaración de los dos hilos
    pthread_t thread1, thread2;

    //Creación de los hilos que ejecutan las funciones anteriores
    pthread_create(&thread1, NULL, &count01, NULL);
    pthread_create(&thread2, NULL, &count02, NULL);

    //Espera a que ambos hilos terminen su ejecución
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    exit(0);
}