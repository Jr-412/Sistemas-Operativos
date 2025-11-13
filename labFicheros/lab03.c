/*
*	Autor: Juan Diego Rojas Osorio
*	Materia: Sistemas Operativos
*	Tema: sistema de ficheros
*	Descripción:
*		- 
*	*******************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

int main(){
  int er;  //Variable para verificar errores
  char nomdir[100], nomfich[100], resp[30];  //Arreglos de caracteres para almacenar el nombre del directorio, el nombre del fichero y la respuesta
  struct stat atr;  //Estructura usada para almacenar los atributos del fichero
  DIR *d;  //Puntero a un objeto DIR, el cual es usado para el manejo de directorios
  struct dirent *rd1;  //Puntero a un objeto dirent, el cual es usado para el manejo de directorios
  time_t fecha;  //Fecha actual

  printf("Nombre del directorio\n");
  fgets(nomdir, sizeof(nomdir), stdin);  //Se lee el nombre del directorio
  // Hay que quitar el \n del nombre del directorio
  nomdir[strlen(nomdir)-1] = '\0';
  fecha = time(&fecha);  //Se obtiene la fecha actual
  
  //Se intenta abrir el directorio y si da error se le informa al usuario
  if((d=opendir(nomdir)) == NULL){
    printf("Error al abrir el directorio\n");
    return -1;
    
  }else {  //Si se abre correctamente 
    //Se recorre el directorio 
    while((rd1 = readdir(d)) != NULL) {
      //Se verifica las entradas especiales "." y ".."
      if((strcmp(rd1 -> d_name, ".") != 0) && (strcmp(rd1 -> d_name, "..") != 0)){
        strcpy(nomfich, nomdir);  //Se copia el nombre del directorio al nombre del fichero
        strcat(nomfich, "/");  //Anade una barra al nombre del fichero
        strcat(nomfich, rd1 -> d_name);  //Se anade el nombre del fichero al nombre del directorio
        printf ("fichero: %s:", nomfich);  //Imprime el nombre del fichero
        er = stat(nomfich, &atr);  //obtiene los atributos del fichero
        printf ("modo: %#o", atr.st_mode);  //Imprime el modo del fichero
        //Verifica si tiene permiso de lectura para el propietario
        if ((atr.st_mode & 400) != 0){
          printf ("Permiso R para el propietario\n");
        } else{
          printf ("No permiso R para el propietario\n");
        }
        
        //Verifica si es un directorio o un fichero
        if (S_ISDIR(atr.st_mode)){
          printf ("Es un directorio\n");
        }
        if (S_ISREG(atr.st_mode)){
          //ficheros modificados en los ultimos 10 dias
          if ((fecha - 10*24*60*60) < atr.st_mtime){
            printf("FICHERO: %s fecha acceso %s, en segundos %ld\n", rd1 -> d_name, ctime(&atr.st_mine), atr.st_mtime);
          }
        }
      }
    }
    closedir(d); //Cierra el directorio
  }
}


/*conclusion:
Tras realizar el laboratorio, se concluye que el programa permite comprender de manera mas clara el sistema de ficheros o archivos en dentro del sistema, consolidando los conocimientos vistos en clase sobre el manejo de directorios y ficheros
*/