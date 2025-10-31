
/**********************************************
* Pontificia Universidad Javeriana
* Autor: Juan Diego Rojas Osorio
* Fecha: Octubre 30 2025
* Materia: Sistemas Operativos
* Tema: Uso de interfaz de creacion de hilos PTHREAD
*  
* **********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Arreglo para almacenar los identificadores de los hilos
pthread_t tid[3];     
//Variable global utilizada por los hilos
int counter;  

//Inicialización del mutex para proteger la sección crítica
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;   

//Función que ejecuta cada hilo
void* compute(void *arg) {
    unsigned long i = 0;
    //Bloquea el mutex para acceder a la sección crítica
    pthread_mutex_lock(&lock);
    counter += 1;   
    printf("\n Job %d has started\n", counter);

    //Simula una tarea con un bucle de espera
    for(i = 0; i < (0xFFFFFFFF); i++);

    //Muestra que el hilo ha finalizado su trabajo
    printf("\n Job %d has finished\n", counter);
    //Libera el mutex para que otros hilos puedan entrar
    pthread_mutex_unlock(&lock);
    
    return NULL;    
}

int main(void) {
    int i = 0;
    int error;

    //Crea tres hilos que ejecutan la función compute
    while(i < 3) {
        error = pthread_create(&(tid[i]), NULL, &compute, NULL);  
 
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        i++;
    }

    //Espera a que los tres hilos terminen su ejecución
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    return 0;
}