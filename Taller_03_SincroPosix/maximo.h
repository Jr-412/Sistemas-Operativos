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
 *    Este programa contiene las declaraciones de variables y funciones que seran luego implementadas por concurrenciaPosix.c
 * "
 *********************************************************************************************/

#ifndef MAXIMO_H
#define MAXIMO_H

#include <pthread.h>

//Estructura para pasar los parámetros a los hilos
struct argHilos{
        int inicio;
        int fin;
        int *vector;
        int maxparcial;
};

typedef struct argHilos param_H;   //Se define un alias para facilitar el uso de la estructura

//Funcion que busca el valor maximo en un segmento del vector, esta sera ejecutada por cada hilo
void *buscarMax(void *parametro);
//Funcion que crea los hilos y calcula el valor maximo del vector
int maximoValor(int *vec, int n, int nhilos);

#endif