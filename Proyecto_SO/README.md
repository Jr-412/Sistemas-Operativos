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

## 📂 Estructura del Proyecto
