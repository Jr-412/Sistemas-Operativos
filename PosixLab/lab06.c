/**********************************************
* Pontificia Universidad Javeriana
* Autor: Juan Diego Rojas Osorio
* Fecha: Octubre 30 2025
* Materia: Sistemas Operativos
* Tema: Uso de interfaz de creacion de hilos PTHREAD
*  
* **********************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


  //Variables globales
int acumulado = 0;
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;


  //Función cálculo de cuadrados

void* cuadrados(void *x) {
    // Se castea el puntero recibido a un entero
    int xi = (intptr_t)x;
    pthread_mutex_lock(&bloqueoCC);
    // Se acumula el cuadrado del número
    acumulado += xi * xi;
    pthread_mutex_unlock(&bloqueoCC);
    return NULL;
}


  //Proceso principal

int main() {
    // Declaración y creación de 20 hilos
    pthread_t WorkersTh[20];

    // Crear los hilos y pasar como argumento un número distinto a cada uno
    for (int i = 0; i < 20; i++) {
        pthread_create(&WorkersTh[i], NULL, cuadrados, (void *)(intptr_t)(i + 1));
    }

    // Esperar a que cada hilo termine su ejecución
    for (int i = 0; i < 20; i++) {
        void *acumulado;
        pthread_join(WorkersTh[i], &acumulado);
    }

    // Mostrar el resultado acumulado de la suma de cuadrados
    printf("Valor suma cuadrados = %d\n", acumulado);

    return 0;
}