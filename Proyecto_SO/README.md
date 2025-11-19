# 🏞️ Sistema de Gestión de Reservas del Parque  
### *Proyecto Final – Sistemas Operativos*  
**Pontificia Universidad Javeriana**

---

## 📌 Descripción General

Este proyecto implementa un sistema de gestión de reservas para un parque recreativo utilizando **procesos independientes**, **pipes nominales (FIFOs)** e **hilos (pthreads)**. El sistema simula la interacción entre múltiples *agentes* que solicitan reservas y un *controlador* encargado de administrarlas, manteniendo la consistencia del aforo, la asignación de horarios y la reprogramación cuando es necesario.

Incluye un **reloj interno** que avanza la hora del parque, libera recursos y genera eventos sin bloquear la comunicación externa, además de mecanismos de sincronización para evitar condiciones de carrera.

---

## 🧩 Arquitectura del Sistema

El sistema se compone de tres módulos principales:

### 🟦 Controlador (`controlador.c`)
Proceso principal encargado de:
- Recibir solicitudes desde múltiples agentes.
- Validar disponibilidad y horarios.
- Administrar el aforo del parque con estructuras protegidas por mutex.
- Reprogramar o rechazar solicitudes según reglas del sistema.
- Avanzar el tiempo mediante un **hilo reloj**.
- Enviar respuestas inmediatas por pipes nominales.
- Generar un reporte final al finalizar la simulación.

### 🟩 Agente (`agente.c`)
Procesos autónomos que:
- Leen solicitudes desde archivos CSV.
- Se registran ante el controlador.
- Envían solicitudes a través de pipes.
- Reciben respuestas de aprobación, reprogramación o rechazo.
- Notifican al controlador cuando terminan.

### 🟧 Utilidades
Incluye múltiples archivos de apoyo:
- `protocolo.h`: define la estructura de los mensajes.
- `pipes.h` / `pipes.c`: funciones para manejo de pipes FIFO.
- `log.h` / `log.c`: registro de eventos.
- `Makefile`: automatiza la compilación del proyecto.

---

## ⏱️ Simulación del Tiempo

El controlador ejecuta un hilo independiente (`hilo_reloj`) que:
- Avanza la hora cada *segundos_por_hora* configurados.
- Libera aforo después de dos horas de uso.
- Imprime el estado del parque periódicamente.
- Finaliza la simulación al alcanzar `hora_fin`.

---

## 🧵 Concurrencia y Sincronización

Se emplea un **mutex global (`mutex_parque`)** para evitar condiciones de carrera al modificar:
- `hora_actual`
- `ocupacion_actual`
- `personas_por_hora[]`
- Lista de solicitudes del parque

Solo un hilo puede modificar estas estructuras al mismo tiempo.

---
## 🧪 Como se prueba?
Para probar este proyecto se requiere usar un archivo de texto, el cual sera leido por el agente. El archivo cuenta con la siguiente estructura:

Lopez,8,10
Martinez,8,12
Torres,9,4
Garcia,7,6

---

## 🛠️ Compilación
Para realizar la compilacion del proyecto se realizo un archivo Makefile con el fin de automatizar el proceso. A continuacion se explica el paso a paso:

**Paso 1**
Se eliminan posibles archivos ejecutables para hacer nuevos con el siguiente comando:
```bash
make clean
```
**Paso 2**
Se realiza la compilacion de todos los programas con el siguiente comando:
```bash
make 
```
**Paso 3**
Tras haber compilado todo pasamos con la ejecucion. Para el proyecto se necesitan al menos 2 terminales diferentes para su funcionamiento. A continuacion, se muestra la terminal que sera usada como el controlador y esta sera ejecutada con el siguiente comando:
```bash
./controlador -i horaIni -f horaFin -s segHoras -t total -p pipeRecibe
```
Ahora solo queda reemplazar los valores de la siguiente manera:
--horaIni-- = Hace referencia a la hora de apertura del parque, para el proyecto se usa 7
--horaFin-- = Hace referencia a la hora de cierre del parque, para el proyecto se usa 19
--segHoras-- = Hace referencia a cuantos segundos dura la simulacion de una hora dentro del sistema, para el proyecto se usa 2
--total-- = Hace referencia al aforo maximo del parque, para el proyecto se usa 300
--pipeRecibe-- = Hace referencia a la ruta donde se encuentra el pipe donde se reciben las solicitudes, para el proyecto se usa /tmp/pipe_controlador

A continuacion, se muestra la terminal que sera usada como el agente y esta sera ejecutada con el siguiente comando:
```bash
./agente -s nombre -a fileSolicitud -p pipeRecibe
```
Ahora solo queda reemplazar los valores de la siguiente manera:
--nombre-- = Hace referencia al nombre que se le asignara al agente, en el proyecto se usa A1
--fileSolicitud-- = Hace referencia al nombre del archivo de donde se tomaran las solicitudes a enviar, este debe estar en la misma carpeta donde se encuentre el codigo del proyecto, en el proyecto se usa solicitudes1.txt
--pipeRecibe-- = Hace referencia al directorio del pipe donde se enviaran las solicitudes, para el proyecto se usa /tmp/pipe_controlador

**Nota**
Ambas terminales se deben de ejecutar simultaneamente para que funcione.

---
Tras haber ejecutado el proyecto se vera en consola el proceso de comunicacion entre cliente-servidor a traves de pipes, evidenciando el envio de solitudes y la programacion de reservas en el parque
