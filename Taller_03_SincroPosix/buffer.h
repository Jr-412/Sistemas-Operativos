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
 *  Este programa contiene las declaraciones de variables y funciones que seran luego implementadas por posixSincro.c
 * "
 *********************************************************************************************/

#ifndef BUFFER_H
#define BUFFER_H

#define MAX_BUFFERS 10

#include <pthread.h>

//se define el numero maximo de buffers
#define MAX_BUFFERS 10  

//Variables globales
extern char buf [MAX_BUFFERS] [100];   //Buffer de 100 caracteres
extern int buffer_index;  //Indice del buffer, donde el productor escribe
extern int buffer_print_index;  //Indice del buffer a imprimir, donde el consumidor lee

//Variables de sincronización
extern pthread_mutex_t buf_mutex;  //Mutex para el buffer
extern pthread_cond_t buf_cond;     //Condición para el buffer
extern pthread_cond_t spool_cond;   //Condición para el spooler

//Variables de control del estado del buffer
extern int buffers_available;     //Numero de buffers disponibles, este es el numero maximo de buffers              
extern int lines_to_print;                 //Numero de lineas a imprimir, este es el numero de buffers ocupados

//Funciones de los hilos
void *producer (void *arg);
void *spooler (void *arg);

#endif