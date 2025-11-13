#Laboratorio sistemas de ficheros
Aca se encuentran los tres programas usados para los laboratorios, los cuales exploran el funcionamiento de funciones para el manejo de ficheros.

#Laboratorio 1
Este programa accede al fichero readme.txt para mostrar su contenido
Este se compila usando el comando **gcc**:
```bash
gcc lab01.c -o prueba
```
Y se ejecuta de la siguiente manera:
```bash
./prueba
```
#Laboratorio 2
Este programa solicita al usuario un nombre de un directorio y muestra una lista de todos los ficheros dentro de el, junto con su tamaño en bytes
Este se compila usando el comando **gcc**
```bash
gcc lab02.c -o prueba
```
Y se ejecuta de la siguiente manera:
```bash
./prueba
```
```bash
.
```
#Laboratorio 3
Este programa, al igual que el anterior, muestra una lista de todos los ficheros dentro de un directorio, sin embargo, este lo hace incluyendo mas detalles como los permisos de lectura del propietario, el tipo de archivo y la fecha de modificacion dentro de los ultimos 10 dias
Este se compila usando el comando **gcc**
```bash
gcc lab02.c -o prueba
```
Y se ejecuta de la siguiente manera:
```bash
./prueba
```
```bash
.
```
#Uso del Makefile
Para automatizar el proceso de compilacion se incluyo un archivo Makefile, este permite compilar los programas. Se utiliza de la siguiente manera:
```bash
make clean
```
Aca se eliminan archivos compiables anteriores 
```bash
make
```
Se compilan todos los programas
```bash
./lab01
```
Aca se debe de cambiar el numero dependiendo de que laboratorio se desea ejecutar
