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
 *  Este programa contiene las implementaciones de funciones y variables que seran luego implementadas por posixSincro.c
 * "
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "buffer.h"

char buf[MAX_BUFFERS][100];
int buffer_index = 0;
int buffer_print_index = 0;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;

int buffers_available = MAX_BUFFERS;
int lines_to_print = 0;


void *producer (void *arg){
  int i, r;
  int my_id = *((int *) arg);  //Identificador del hilo productor
  int count = 0;

  //Cada productor escribira 10 lineas
  for (i = 0; i < 10; i++) {

      //Bloquea el mutex antes de acceder al buffer
      if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
          fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
      }
      //Si no hay buffers disponibles el hilo productor espera
          while (!buffers_available) 
              pthread_cond_wait (&buf_cond, &buf_mutex);

          //Escribe en el buffer
          int j = buffer_index;
          buffer_index++;
          if (buffer_index == MAX_BUFFERS)
              buffer_index = 0;
          buffers_available--;  //Disminuye el numero de buffers disponibles

          //Escribe el mensaje en el buffer
          sprintf (buf [j], "Thread %d: %d\n", my_id, ++count);
          lines_to_print++;  //Incrementa el numero de lineas a imprimir

          pthread_cond_signal (&spool_cond);  //Le indica al spooler que hay una linea nueva a imprimir

      //Libera el mutex para los demas hilos
      if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
          fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
      }

      sleep (1);
  }
}

void *spooler (void *arg){
  int r;

  //Ciclo infinito, este sera cancelado por el hilo principal cuando ya no haya mas lineas a imprimir
  while (1) {  

      //Bloquea el mutex antes de acceder al buffer
      if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
          fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
      }

      //Espera a que haya lineas para imprimir
          while (!lines_to_print) 
              pthread_cond_wait (&spool_cond, &buf_mutex);

      //Imprime el mensaje mas antiguo en el buffer
          printf ("%s", buf [buffer_print_index]);
          lines_to_print--;  //disminuye el numero de lineas a imprimir

      //Mueve el indice del buffer a imprimir
          buffer_print_index++;
          if (buffer_print_index == MAX_BUFFERS)
             buffer_print_index = 0;

      //Libera espacio y avisa a los hilos productores
          buffers_available++;
          pthread_cond_signal (&buf_cond);

      //Libera el mutex
      if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
          fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
      }

  }
}