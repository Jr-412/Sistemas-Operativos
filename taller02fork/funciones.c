/****************************************************************************** 
* Pontificia Universidad Javeriana
* Autores: 
Juan Diego Rojas Osorio 
Juan Jose Ballesteros Suarez
* Fecha: 30/10/2025 
* Materia: Sistemas Operativos
* Docente: J.Corredor
* Descripción: Se realiza la implementacion de las funciones anteriormente
* declaradas en el archivo modulo.h
* **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "funciones.h"



//Función para leer archivo y cargar arreglo dinámico
int* leerArchivo(const char* nombre_archivo, int n) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Se reserva memoria para el arreglo
    int* arreglo = (int*)malloc(n * sizeof(int));
    if (arreglo == NULL) {
        perror("Error en la asignación de memoria");
        fclose(archivo);
        exit(EXIT_FAILURE);
    }

    // Se lee el archivo y se carga el arreglo
    for (int i = 0; i < n; i++) {
        if (fscanf(archivo, "%d", &arreglo[i]) != 1) {
            fprintf(stderr, "Error en la lectura del elemento %d\n", i);
            free(arreglo);
            fclose(archivo);
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
    return arreglo;
}

// Función para calcular suma de un arreglo
long calcularSuma(int* arreglo, int n) {
    long suma = 0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i];
    }
    return suma;
}


//Función ejecutada por el nieto (grand hijo)
void procesoNieto(int* arreglo, int n, int pipe_escritura) {
    long sumaA = calcularSuma(arreglo, n);
    printf("[Nieto PID=%d] Realizando calculo de sumaA del archivo00...\n", getpid());
    printf("[Nieto PID=%d] SumaA = %ld\n", getpid(), sumaA);

    // Se envía sumaA al primer hijo
    write(pipe_escritura, &sumaA, sizeof(long));
    close(pipe_escritura);

    exit(EXIT_SUCCESS);
}


//Función ejecutada por el segundo hijo
void procesoSegundo_hijo(int* arreglo, int n, int pipe_escritura) {
    long sumaB = calcularSuma(arreglo, n);
    printf("[Segundo Hijo PID=%d] Realizando calculo de sumaB del archivo01...\n", getpid());
    printf("[Segundo Hijo PID=%d] SumaB = %ld\n", getpid(), sumaB);

    // Se envía sumaB al primer hijo
    write(pipe_escritura, &sumaB, sizeof(long));
    close(pipe_escritura);

    exit(EXIT_SUCCESS);
}

//Función ejecutada por el primer hijo
void procesoPrimer_hijo(int* arreglo1, int n1, int* arreglo2, int n2,
                         int pipe_nieto[2], int pipe_hijo2[2], int pipe_padre[2]) {

    // Se crea segundo hijo (hermano)
    pid_t pid_hijo2 = fork();

    if (pid_hijo2 < 0) {
        perror("Error en la creación del segundo hijo");
        exit(EXIT_FAILURE);
    }

    if (pid_hijo2 == 0) {
        
        // Se cierra lectura
        close(pipe_hijo2[0]); 
        procesoSegundo_hijo(arreglo2, n2, pipe_hijo2[1]);
    }

    // Crear nieto (hijo del primer hijo)
    pid_t pid_nieto = fork();

    if (pid_nieto < 0) {
        perror("Error en la creación del nieto");
        exit(EXIT_FAILURE);
    }

    if (pid_nieto == 0) {
        // Cerrar lectura
        close(pipe_nieto[0]); 
        procesoNieto(arreglo1, n1, pipe_nieto[1]);
    }

    // Se continúa: recibe sumaA y sumaB
    close(pipe_nieto[1]);
    close(pipe_hijo2[1]);
    close(pipe_padre[0]);

    long sumaA, sumaB;

    // Se recibe sumaA del nieto
    read(pipe_nieto[0], &sumaA, sizeof(long));
    close(pipe_nieto[0]);

    // Se recibe sumaB del segundo hijo
    read(pipe_hijo2[0], &sumaB, sizeof(long));
    close(pipe_hijo2[0]);

    // Se espera a que terminen los procesos hijos
    wait(NULL); 
    wait(NULL); 

    // Se calcula la suma total
    long suma_total = sumaA + sumaB;
    printf("[Primer Hijo PID=%d] Realizando calculo de suma total...\n", getpid());
    printf("[Primer Hijo PID=%d] Suma Total = %ld + %ld = %ld\n", 
           getpid(), sumaA, sumaB, suma_total);

    // Enviar las tres sumas al padre
    write(pipe_padre[1], &sumaA, sizeof(long));
    write(pipe_padre[1], &sumaB, sizeof(long));
    write(pipe_padre[1], &suma_total, sizeof(long));
    close(pipe_padre[1]);

    exit(EXIT_SUCCESS);
}


//Funcion ejecutada por el proceso padre
void procesoPadre(int pipe_lectura) {
    long sumaA, sumaB, suma_total;

    // Se reciben los tres valores del primer hijo
    read(pipe_lectura, &sumaA, sizeof(long));
    read(pipe_lectura, &sumaB, sizeof(long));
    read(pipe_lectura, &suma_total, sizeof(long));
    close(pipe_lectura);

    // Se espera a que termine el primer hijo
    wait(NULL);

    // Se imprimen los resultados finales
    printf("\n=== Resultados (Padre PID=%d) ===\n", getpid());
    printf("SumaA (archivo00): %ld\n", sumaA);
    printf("SumaB (archivo01): %ld\n", sumaB);
    printf("Suma Total: %ld\n", suma_total);
    printf("=====================================\n");
}
