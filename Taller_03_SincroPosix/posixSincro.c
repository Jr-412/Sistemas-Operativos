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
 *  El programa implementa un sistema productor–consumidor concurrente haciendo uso de hilos POSIX (pthread), 
 *  exclusión mutua (mutexes) y variables de condición para coordinar el acceso a un buffer compartido.
 * "
 *********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "buffer.h"


int main (int argc, char **argv){
    
    pthread_t tid_producer [10], tid_spooler;  //Arreglo de 10 hilos productores y un hilo consumidor (spooler)
    int i, r;

    buffer_index = buffer_print_index = 0;  //Se inicializan los indices del buffer

    //Se crea el hilo consumidor (spooler)
    if ((r = pthread_create (&tid_spooler, NULL, spooler, NULL)) != 0) {
        fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
    }

    //Se crean los hilos productores, en este caso 10 hilos
    int thread_no [10];
    for (i = 0; i < 10; i++) {
        thread_no [i] = i;  //Cada hilo cuenta con un identificador unico
        if ((r = pthread_create (&tid_producer [i], NULL, producer, (void *) &thread_no [i])) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    }
    //Se espera a que los hilos productores terminen
    for (i = 0; i < 10; i++)
        if ((r = pthread_join (tid_producer [i], NULL)) == -1) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }

    //Se espera a que el hilo consumidor (spooler) termine de imprimir todas las lineas
    while (lines_to_print) sleep (1);

    //Finaliza el hilo consumidor (spooler) cuando ya no hay mas lineas a imprimir
    if ((r = pthread_cancel (tid_spooler)) != 0) {
        fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
    }

    exit (0);
}


