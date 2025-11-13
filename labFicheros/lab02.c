/*
*	Autor: Juan Diego Rojas Osorio
*	Materia: Sistemas Operativos
*	Tema: sistema de ficheros
*	Descripción:
*		- 
*	*******************
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <dirent.h>


int main(){
  DIR *d;  //Puntero a un objeto DIR, el cual es usado para el manejo de directorios
  char nomdir[90], nomfich[90];  //Arreglos de cararcteres que almacenan el nombre del directorio y el nombre del fichero
  struct stat datos;
  struct dirent *direc;

  printf("Introduzca el nombre del directorio: ");
  fgets(nomdir, sizeof(nomdir), stdin);
  nomdir[strlen(nomdir)-1] = '\0'; //Eliminamos el \n del nombre del fichero

  //Se intenta abrir el directorio y si da error se le informa al usuario
  if((d=opendir(nomdir)) == NULL){
    printf("Error al abrir el directorio\n");
    return -1;
  }

  //Se recorre el directorio
  while((direc = readdir(d)) != NULL){
    strcpy(nomfich, nomdir); //Se copia el nombre del directorio al nombre del fichero
    strcat(nomfich, "/");  //Anade una barra al nombre del fichero
    strcat(nomfich, direc->d_name);  //Se anade el nombre del fichero al nombre del directorio
    stat (nomfich, &datos);  //obtiene los atributos del fichero

    //Verifica si es un directorio o un fichero
    if(S_ISREG(datos.st_mode))
      printf ("Nombre: %s\t| Tamaño: %ld\n", direc->d_name, datos.st_size);
  }
  closedir(d);
}

/*
Conclusion: Tras realizar el laboratorio, se concluye que el programa permite comprender el uso de funciones como opendir, readdir y closedir, las cuales ofrecen una manera mas eficiente de manejar directorios y ficheros, ademas de obtener informacion de los mismos. Por ultimo, nos indica que la utilizacion de estas funciones resulta util para el desarrollo de herramientos de gestion o analisis de ficheros.
*/