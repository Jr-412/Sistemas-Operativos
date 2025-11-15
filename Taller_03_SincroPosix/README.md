# 🧵 **Taller 03 – Sincronización POSIX**

**Pontificia Universidad Javeriana**  
**Curso:** Sistemas Operativos  
**Profesor:** John Jairo Corredor Franco  
**Fecha:** 20 de noviembre de 2025  

## 👥 **Integrantes**

- Juan José Ballesteros  
- Juan Diego Rojas  

---

## 🧠 **Introducción**

Este taller tiene como finalidad **aplicar mecanismos de sincronización POSIX** para resolver dos problemas clásicos en Sistemas Operativos utilizando **concurrencia**, **hilos POSIX (pthread)**, **mutex**, **variables de condición**, **semaforos POSIX**, y **memoria compartida (mmap/shm_open)**.

Los dos programas desarrollados fueron:

### ✔️ **1. Productor–Consumidor con pthreads (mutex + variables de condición)**  
Implementa una cola circular de mensajes usando:
- `pthread_mutex_t`  
- `pthread_cond_t`  
- 10 productores  
- 1 consumidor (spooler)

El sistema garantiza que los productores no escriben cuando el buffer está lleno, y el consumidor no lee cuando está vacío.

### ✔️ **2. Productor–Consumidor con semáforos POSIX + Memoria Compartida**  
Implementa el mismo problema pero con **procesos independientes**, usando:
- `sem_open()`
- `shm_open()`
- `mmap()`

Un proceso escribe en un buffer circular y otro lo consume, simulando IPC real entre procesos.

### ✔️ **3. Búsqueda del Máximo en un Vector con pthreads**  
El vector se divide entre N hilos; cada hilo calcula un máximo parcial y el hilo principal obtiene el máximo global.

---

## 🎯 **Objetivos del Taller**

- Comprender y aplicar los mecanismos de sincronización POSIX:
  - Mutex
  - Variables de condición
  - Semáforos POSIX
  - Memoria compartida
- Implementar soluciones concurrentes que eviten:
  - Condiciones de carrera  
  - Inconsistencias  
  - Deadlocks  
- Modularizar y organizar adecuadamente programas basados en concurrencia.
- Analizar el comportamiento de procesos/hilos y su interacción con memoria compartida y sincronización.

---

## 🧩 **Programas Incluidos**

| Programa | Descripción |
|---------|-------------|
| `posixSincro.c` | Productor–Consumidor usando hilos, mutex y variables de condición |
| `buffer.c / buffer.h` | Módulo separado del buffer circular y la sincronización |
| `producer.c` | Proceso productor usando semáforos + memoria compartida |
| `consumer.c` | Proceso consumidor usando semáforos + memoria compartida |
| `maximoMain.c` | Lee archivo y ejecuta búsqueda del máximo utilizando hilos |
| `maximo.c / maximo.h` | Lógica de búsqueda del máximo y creación de hilos |
| `Makefile` | Automatiza la compilación de todos los módulos |



---

## 🧳 **Cómo Ejecutar los Programas**

El proyecto incluye un **Makefile** para automatizar la compilación.

---

### **🟢 Paso 1 — Limpiar compilaciones previas**

```bash
make clean
```

---

### **🟢 Paso 2 — Compilar todos los programas**

```bash
make
```

Esto generará:

- `productorConsumidorPosix`
- `productor`
- `consumidor`
- `maximo`

---

### **🟢 Paso 3 — Ejecutar Productor–Consumidor con pthread**

```bash
./productorConsumidorPosix
```

---

### **🟢 Paso 4 — Ejecutar Productor–Consumidor con procesos (IPC)**

En una terminal:

```bash
./productor
```

En otra terminal:

```bash
./consumidor
```

---

### **🟢 Paso 5 — Ejecutar búsqueda del máximo**

Asegurarse de tener un archivo como:

```
10
3 9 12 4 8 2 5 30 1 7
```

Luego ejecutar:

```bash
./maximo datos.txt 4
```

(4 hilos)

---

## 📊 **Resultados esperados**

- El programa Productor–Consumidor **no pierde mensajes** y mantiene el orden FIFO.
- Los productores no sobrescriben cuando el buffer está lleno.
- El consumidor imprime exactamente 100 líneas (10 hilos × 10 mensajes).
- El sistema con semáforos utiliza correctamente IPC real.
- Los tiempos de ejecución del programa del máximo disminuyen al aumentar los hilos (hasta cierto punto).

---

## 🧠 **Conclusiones del Taller**

Este taller permitió comprender de forma práctica el funcionamiento de los mecanismos de sincronización de POSIX, demostrando que la concurrencia requiere un control cuidadoso para evitar problemas como condiciones de carrera, bloqueos o inconsistencias. La implementación del modelo Productor–Consumidor con pthreads y con procesos independientes evidenció las diferencias entre sincronización en memoria compartida dentro de un proceso y sincronización real entre procesos del sistema. Finalmente, la experiencia modularizando código y utilizando Makefiles contribuyó a fortalecer la organización y escalabilidad del proyecto.

---
