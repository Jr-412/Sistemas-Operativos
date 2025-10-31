/****************************************************
* Pontificia Universidad Javeriana
* Docente: J. Corredor
* Autor: Juan Diego Rojas Osorio
* Fecha: 23/10/2025
* Materia: Sistemas Operativos
* Objetivo: Crear dos hilos y ver que su ejecucción es
*           independiente uno del otro, se crean sin
*	    un orden especifico.
****************************************************/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

//Función que imprime el mensaje recibido como parámetro
void *print_message_function( void *ptr ) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}

void main() {
    //Declaración de dos hilos
    pthread_t thread1, thread2;
    //Mensajes que cada hilo mostrará
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;

    /* Creación de los hilos, cada uno ejecutará la misma función de impresión */
    iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
    
    //Muestra los valores de retorno de la creación de cada hilo
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
    exit(0);
}
