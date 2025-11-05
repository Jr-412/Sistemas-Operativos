/*************************************************************************** 
* Pontificia Universidad Javeriana
* Autores: 
Juan Diego Rojas Osorio 
Juan Jose Ballesteros Suarez
* Fecha: 30/10/2025
* Materia: Sistemas Operativos
* Docnete_ J.Corredor
* Descripción: Programa principal, encargado de la creacion de los procesos y la
*  ejecucion de las funciones declaradas en el archivo modulo.h
********************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "funciones.h"

int main(int argc, char* argv[]) {
    // Se realiza la validación de argumentos
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        fprintf(stderr, "  N1: cantidad de elementos en archivo00\n");
        fprintf(stderr, "  archivo00: fichero con arreglo de enteros\n");
        fprintf(stderr, "  N2: cantidad de elementos en archivo01\n");
        fprintf(stderr, "  archivo01: fichero con arreglo de enteros\n");
        exit(EXIT_FAILURE);
    }

    // Se leen los argumentos
    int N1 = atoi(argv[1]);
    char* archivo00 = argv[2];
    int N2 = atoi(argv[3]);
    char* archivo01 = argv[4];

    // Se valida que N1 y N2 sean positivos
    if (N1 <= 0 || N2 <= 0) {
        fprintf(stderr, "Error: N1 y N2 deben ser valores positivos\n");
        exit(EXIT_FAILURE);
    }

    printf("***** Taller Fork *****\n");
    printf("Leyendo archivos...\n");
    printf("Archivo 1: %s (N1=%d)\n", archivo00, N1);
    printf("Archivo 2: %s (N2=%d)\n\n", archivo01, N2);

    // Lectura de archivos y carga de arreglos
    int* arreglo1 = leerArchivo(archivo00, N1);
    int* arreglo2 = leerArchivo(archivo01, N2);

    // Creación de pipes
    int pipe_nieto_hijo[2];    // Pipe nieto hacia primer hijo
    int pipe_hijo2_hijo1[2];   // Pipe segundo hijo hacia primer hijo
    int pipe_hijo1_padre[2];   // Pipe primer hijo hacia padre

    if (pipe(pipe_nieto_hijo) == -1 || pipe(pipe_hijo2_hijo1) == -1 || pipe(pipe_hijo1_padre) == -1) {
        perror("Error en la creación de pipes");
        free(arreglo1);
        free(arreglo2);
        exit(EXIT_FAILURE);
    }

    // Creación del primer hijo
    pid_t pid_hijo1 = fork();

    if (pid_hijo1 < 0) {
        perror("Error en la creación del primer hijo");
        free(arreglo1);
        free(arreglo2);
        exit(EXIT_FAILURE);
    }

    if (pid_hijo1 == 0) {
        // Proceso primer hijo
        

        // Creación del segundo hijo (hermano)
        pid_t pid_hijo2 = fork();

        if (pid_hijo2 < 0) {
            perror("Error en la creación del segundo hijo");
            exit(EXIT_FAILURE);
        }

        if (pid_hijo2 == 0) {
            // Proceso segundo hijo
            // Se calcula sumaB del arreglo2 (archivo01)

            close(pipe_hijo2_hijo1[0]); // Cerrar lectura

            long sumaB = calcularSuma(arreglo2, N2);
            printf("[Segundo Hijo PID=%d] Calculando sumaB del archivo01...\n", getpid());
            printf("[Segundo Hijo PID=%d] SumaB = %ld\n", getpid(), sumaB);

            // Se envía sumaB al primer hijo
            write(pipe_hijo2_hijo1[1], &sumaB, sizeof(long));
            close(pipe_hijo2_hijo1[1]);

            exit(EXIT_SUCCESS);
        }

        // Creación del nieto (hijo del primer hijo)
        pid_t pid_nieto = fork();

        if (pid_nieto < 0) {
            perror("Error en la creación del nieto");
            exit(EXIT_FAILURE);
        }

        if (pid_nieto == 0) {
            // Proceso nieto
            // Se calcula sumaA del arreglo1 (archivo00)

            close(pipe_nieto_hijo[0]); // Cerrar lectura

            long sumaA = calcularSuma(arreglo1, N1);
            printf("[Nieto PID=%d] Calculando sumaA del archivo00...\n", getpid());
            printf("[Nieto PID=%d] SumaA = %ld\n", getpid(), sumaA);

            // Se envía sumaA al primer hijo
            write(pipe_nieto_hijo[1], &sumaA, sizeof(long));
            close(pipe_nieto_hijo[1]);

            exit(EXIT_SUCCESS);
        }

        // Primer hijo recibe sumaA y sumaB
        close(pipe_nieto_hijo[1]);     // Cerrar escritura
        close(pipe_hijo2_hijo1[1]);    // Cerrar escritura
        close(pipe_hijo1_padre[0]);    // Cerrar lectura

        long sumaA, sumaB;

        // Se recibe la sumaA del nieto
        read(pipe_nieto_hijo[0], &sumaA, sizeof(long));
        close(pipe_nieto_hijo[0]);

        // Se recibe la sumaB del segundo hijo
        read(pipe_hijo2_hijo1[0], &sumaB, sizeof(long));
        close(pipe_hijo2_hijo1[0]);

        // Se espera a que terminen los procesos hijos
        wait(NULL); // Esperar al nieto
        wait(NULL); // Esperar al segundo hijo

        // Se calcula la suma total
        long suma_total = sumaA + sumaB;
        printf("[Primer Hijo PID=%d] Calculando suma total...\n", getpid());
        printf("[Primer Hijo PID=%d] Suma Total = %ld + %ld = %ld\n", 
               getpid(), sumaA, sumaB, suma_total);

        // Se envían las tres sumas al padre
        write(pipe_hijo1_padre[1], &sumaA, sizeof(long));
        write(pipe_hijo1_padre[1], &sumaB, sizeof(long));
        write(pipe_hijo1_padre[1], &suma_total, sizeof(long));
        close(pipe_hijo1_padre[1]);

        exit(EXIT_SUCCESS);
    }

    // Proceso padre
    // Se recibe los resultados finales del primer hijo

    close(pipe_hijo1_padre[1]); // Cerrar escritura

    long sumaA, sumaB, suma_total;

    // Se reciben los tres valores del primer hijo
    read(pipe_hijo1_padre[0], &sumaA, sizeof(long));
    read(pipe_hijo1_padre[0], &sumaB, sizeof(long));
    read(pipe_hijo1_padre[0], &suma_total, sizeof(long));
    close(pipe_hijo1_padre[0]);

    // Se espera a que termine el primer hijo
    wait(NULL);

    // Se imprimen los resultados finales
    printf("\n***** Resultados (Padre PID=%d) *****\n", getpid());
    printf("SumaA (archivo00): %ld\n", sumaA);
    printf("SumaB (archivo01): %ld\n", sumaB);
    printf("Suma Total: %ld\n", suma_total);
    printf("******************************************\n");

    // Liberación de memoria
    free(arreglo1);
    free(arreglo2);

    return EXIT_SUCCESS;
}
