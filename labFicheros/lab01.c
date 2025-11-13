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

int main(int argc, char *argv[]){
    char *nombrefichero = "readme.txt";  //Nombre del fichero que se va a leer
    FILE *fp = fopen(nombrefichero, "r");  //Apertura del fichero en modo lectura

  //Se verifica si el fichero se abrio correctamente
    if (fp==NULL){
        printf("Error: no se puede abrir el fichero\n");
        return 1;
    }

    printf("\n=======================================\n");
    printf("\n LECTURA DE FICHERO readme.txt\n");
    printf("\n=======================================\n");

    //Lectura de fichero, máximo 256 bytes por línea
    //Lectura de línea por línea (buscar \n)
    const unsigned LARGO_MAX_LINEA = 256;
    char buffer[LARGO_MAX_LINEA];

  //Se lee el fichero linea por linea para luego imprimirlo
    while(fgets(buffer,LARGO_MAX_LINEA,fp))
        printf("%s", buffer);

    /*CERRAR EL FICHERO*/
    fclose(fp);

    return 0;
} 

/*
Conclusion: Tras realizar el laboratorio, se concluye que el programa nos permite ver de manera mas clara como se realiza la lectura de un fichero en el lenguaje de programacion c
*/