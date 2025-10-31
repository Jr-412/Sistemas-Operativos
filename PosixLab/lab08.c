/**********************************************
* Pontificia Universidad Javeriana
* Autor: Juan Diego Rojas Osorio
* Fecha: Octubre 30 2025
* Materia: Sistemas Operativos
* Tema: Se tiene 2 funciones para asignar y reportar en funcion de la llamada desde los hilos creados, desde el proceso principal
*  
* **********************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


  //Variables globales

int valor = 100;
bool notificar = false;
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condiCC = PTHREAD_COND_INITIALIZER;


void* reportar(void *nousada) {
    pthread_mutex_lock(&bloqueoCC);
    // Se acumula el cuadrado del número
    while (!notificar) {
        pthread_cond_wait(&condiCC, &bloqueoCC);
    }
    printf("Valor = %d\n", valor);
    pthread_mutex_unlock(&bloqueoCC);
    return NULL;
}
void* asignar(void *nousada){
    valor = 20;
    pthread_mutex_lock(&bloqueoCC);
    notificar = true;
    pthread_cond_signal(&condiCC);
    pthread_mutex_unlock(&bloqueoCC);
    return NULL;
}

int main() {

          //Declaración y creación de hilos
          //Se definen dos hilos: uno para reportar y otro para asignar.

        pthread_t reporte, asigne;

        //Se crean los dos hilos y se asocian con sus funciones correspondientes
        pthread_create(&reporte, NULL, &reportar, NULL);
        pthread_create(&asigne, NULL, &asignar, NULL);


          //Variable para recoger el valor al esperar la finalización
          //de los hilos (pthread_join).

        void *nousada;

        //Espera a que cada hilo termine su ejecución 
        pthread_join(reporte, &nousada);
        pthread_join(asigne, &nousada);


        return 0;

}