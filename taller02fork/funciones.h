/**********************************************************************
* Pontificia Universidad Javeriana
* Autores: 
Juan Diego Rojas Osorio 
Juan Jose Ballesteros Suarez
* Fecha: 30/10/2025 
* Materia: Sistemas Operativos
* Docente_ J.Corredor
* Archivo: modulo.h
* Descripción: Se realiza la declaracion de las funciones que seran utilizadas
*  en el programa principal
**************************************************************************
*/

#ifndef FUNCIONES_H
#define FUNCIONES_H
// Funcion que lee un archivo y carga un arreglo dinámico
int* leerArchivo(const char* nombre_archivo, int n);

// Función que calcula la suma de un arreglo
long calcularSuma(int* arreglo, int n);

// Función que ejecuta el proceso nieto (grand hijo)
void procesoNieto(int* arreglo, int n, int pipe_escritura);

// Función que ejecuta el proceso segundo hijo
void procesoSegundo_hijo(int* arreglo, int n, int pipe_escritura);

// Función que ejecuta el proceso primer hijo
void procesoPrimer_hijo(int* arreglo1, int n1, int* arreglo2, int n2,
                         int pipe_nieto[2], int pipe_hijo2[2], int pipe_padre[2]);

// Función que ejecuta el proceso padre
void procesoPadre(int pipe_lectura);

#endif
