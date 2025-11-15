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
 *  Este programa implementa la parte del productor en el problema de productor-consumidor, esto haciendo uso de memoria compartida y semáforos POSIX.
 * "
 *********************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/mman.h>  // Para mmap y munmap
#include <fcntl.h>     // Para sem_open con O_RDWR
#include <unistd.h>    // Para sleep

#define BUFFER 10  // Tamaño del buffer

// Definir la estructura que será mapeada en memoria compartida
typedef struct {
    int bus[BUFFER];  // Array que representa el buffer circular
    int salida;  // Índice de salida del buffer
    int entrada;
} compartir_datos;

int main() {
    sem_t *vacio = sem_open("/vacio", O_CREAT, 0644, BUFFER);  //Se crea el "semáforo vacio", este con el tamano del buffer
    sem_t *lleno = sem_open("/lleno", O_CREAT, 0644, 0);  //Se crea el "semáforo lleno", este se inicializa en 0
    //Se verifica si los semáforos se crearon correctamente
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    //Se crea la memoria compartida
    int shm_fd = shm_open("/memoria_compartida", O_CREAT | O_RDWR, 0644);

    //Se verifica si la memoria compartida se creo correctamente, si no se le informa al usuario
    if (shm_fd < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    //Se asigna el tamano de la memoria compartida para que sea igual al tamano de la estructura
    ftruncate(shm_fd, sizeof(compartir_datos));

    //Se mapea la memoria compartida en el espacio de direcciones del proceso productor
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    compartir->entrada = 0;

    //Genera y escribe 10 elementos en el buffer
    for (int i = 1; i <= 10; i++) {
        sem_wait(vacio);  //Espera a que haya al menos un espacio vacio en el buffer
        compartir->bus[compartir->entrada] = i;  // Escribe el elemento i en la posición de entrada del buffer
        printf("Productor: Produce %d\n", i);  // Imprime el producto producido
        compartir->entrada = (compartir->entrada + 1) % BUFFER;  // Actualiza la posición de entrada del buffer
        sem_post(lleno);  // Indica que hay un elemento disponible para consumir
        sleep(1);  // Simula el tiempo de producción, en este caso 1 segundo
  }

    //Se cierra la memoria compartida y se liberan los recursos
    munmap(compartir, sizeof(compartir_datos));  //Desmapea la memoria compartida
    close(shm_fd);  //Cierra el descriptor de archivo de la memoria compartida
    sem_close(vacio);  //Cierra el semaforo "vacio"
    sem_unlink("/vacio");  //Elimina el semaforo "vacio"
    shm_unlink("/memoria_compartida");  //Elimina la memoria compartida
    return 0;
}