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
 *    Este programa contiene las implementaciones de funciones que seran luego implementadas por concurrenciaPosix.c
 * "
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "maximo.h"

//Funcion que busca el valor maximo en un segmento del vector, esta sera ejecutada por cada hilo
void *buscarMax(void *parametro){ 
        param_H *argumentos = (param_H *)parametro;  //Se convierte el parametro a la estructura
        argumentos->maxparcial = argumentos->vector[argumentos->inicio];  //Se inicializa el maximo parcial con el primer elemento del segmento

        //Recorre el segmento del vector asignado al hilo
        for(int i=0; i<argumentos->fin; i++){
                if(argumentos->vector[i] > argumentos->maxparcial)
                        argumentos->maxparcial = argumentos->vector[i];
        }
        pthread_exit(0);
        return NULL;
}


int maximoValor(int *vec, int n, int nhilos) {
    pthread_t hilos[nhilos];
    param_H argumentos[nhilos];

    int bloque = n / nhilos;
    int maxglobal = -9999999;

    for (int i = 0; i < nhilos; i++) {
        argumentos[i].inicio = i * bloque;
        argumentos[i].fin = (i == nhilos - 1) ? n : (i + 1) * bloque;
        argumentos[i].vector = vec;

        pthread_create(&hilos[i], NULL, buscarMax, &argumentos[i]);
    }

    // Esperar a los hilos y obtener máximos parciales
    for (int i = 0; i < nhilos; i++) {
        pthread_join(hilos[i], NULL);

        if (argumentos[i].maxparcial > maxglobal)
            maxglobal = argumentos[i].maxparcial;
    }

    return maxglobal;
}