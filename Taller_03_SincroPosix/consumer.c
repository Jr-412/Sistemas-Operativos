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
 *    Este programa implementa la parte consumidora del problema productor-consumidor, en este se hace uso memoria compartida y semáforos POSIX 
 *    para sincronizar dos procesos distintos.
 *********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER 10

// Definir la estructura que será mapeada en memoria compartida
typedef struct {
    int bus[BUFFER];  // Array que representa el buffer circular
    int salida;  // Índice de salida del buffer
} compartir_datos;


int main() {

    sem_t *vacio = sem_open("/vacio", 0);  //Se abre el semaforo "vacio", el cual indica la cantidad de espacios disponibles en el buffer
    sem_t *lleno = sem_open("/lleno", 0);  //Se abre el semaforo "lleno", el cual indica la cantidad de elementos disponibles para consumir

    //Se verifica que los semaforos se hayan abierto correctamente
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    //Se abre la memoria compartida anteriormente creada por el productor
    int fd_compartido = shm_open("/memoria_compartida", O_RDWR, 0644);

    //Verifica si no hubo error al abrir la memoria compartida
    if (fd_compartido < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    //Mapea la memoria al espacio de direcciones del proceso consumidor
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos), PROT_READ | PROT_WRITE, MAP_SHARED, fd_compartido, 0);
    compartir->salida = 0;  //Inicializa el indice de salida en 0

    //El consumidor extraera y mostrara 10 elementos del buffer
    for (int i = 1; i <= 10; i++) {
        sem_wait(lleno);  //Espera a que haya al menos un elemento en el buffer
        int item = compartir->bus[compartir->salida];   //Extrae el elemento actual desde la posicion "salida" del buffer
        printf("Consumidor: Consume %d\n", item);   //Imprime el elemento consumido

    //Actualiza el indice de salida al siguiente elemento del buffer
        compartir->salida = (compartir->salida + 1) % BUFFER; 
        sem_post(vacio);  //Incrementa el semaforo vacio, indicando que hay un espacio disponible en el buffer
        sleep(2);    //Simula el tiempo de consumo del elemento, en este caso 2 segundos
    }

    //Se liberan los recursos usados por el consumidor
    munmap(compartir, sizeof(compartir_datos));  //Desmapea la memoria compartida
    close(fd_compartido);  //Cierra el descriptor de archivo de la memoria compartida
    sem_close(lleno);  //cierra el semaforo lleno
    sem_unlink("/lleno");  //Elimina el semaforo "lleno"
    sem_unlink("/memoria_compartida");  //Se elimina la memoria compartida
    return 0;
}