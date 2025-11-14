# 🚀 Evaluación de Rendimiento en Multiplicación de Matrices 

**Pontificia Universidad Javeriana**  
**Curso:** Sistemas Operativos  
**Profesor:** John Jairo Corredor Franco  
**Fecha:** 13 de noviembre de 2025

## 👥 Integrantes

- Juan Jose Ballesteros
- Nicolas Pinilla
- Juan Diego Rojas

---

## 🧠 Introducción

Este proyecto tiene como objetivo **evaluar el rendimiento** de distintos enfoques de **programación paralela en C** aplicados a la **multiplicación de matrices cuadradas**. Se comparan tres técnicas:

- `OpenMP`
- `fork()` (procesos)
- `POSIX threads (pthread)`
-  `FilasOpenMP (Multiplicacion por la transpuesta)`

Estos algoritmos se ejecutan en **múltiples entornos de cómputo** y se analizaran en función del número de hilos, la arquitectura del sistema y el tamaño de las matrices. Esta evaluación permite comprender el impacto del paralelismo en el rendimiento y eficiencia de aplicaciones intensivas en cómputo.

---

## 🎯 Objetivos

- Comparar el rendimiento entre algoritmos de multiplicacion de matrices de forma secuencial y paralela.
- Medir los tiempos de ejecución en diferentes arquitecturas de software (WSL, Ubuntu VM, Replit).
- Analizar el comportamiento de cada técnica respecto a:
  - Tamaños de matriz: `50, 100, 500, 1000, 1500`
  - Cantidad de hilos: `1, 2, 4, 8, 10`
  - Sistemas con `4, 8, 12 y 16 hilos`

---

## 🛠️ Implementación

Se desarrollaron cuatro programas diferentes en el lenguaje de programacion **C**:

| Algoritmo        | Descripción                                                                 |
|------------------|-----------------------------------------------------------------------------|
| `mmClasicaFork`  | Usa `fork()` para crear procesos hijos, cada uno procesa una parte de la matriz y comunica resultados por `pipe`. |
| `mmClasicaPosix` | Usa `pthread_create()` para distribuir filas entre hilos POSIX.             |
| `mmClasicaOpenMP`| Usa directivas `#pragma` de OpenMP para paralelizar el trabajo.             |
| `mmFilasOpenMP`| Usa directivas `#pragma` de OpenMP para paralelizar el trabajo, esta vez haciendo la multiplicacion por la matriz transpuesta de la matriz B.             |


Cada programa realiza:

1. Reserva dinámica de memoria
2. Inicialización de matrices
3. Multiplicación de matrices
4. Medición de tiempo con `gettimeofday()`
5. Liberación de memoria

---

## 🧪 Método de Prueba

Para automatizar las pruebas:

- Se desarrolló el script `lanza.pl` que:
  - Ejecuta las combinaciones posibles de algoritmos, tamaños de matrices y número de hilos.
  - Repite cada combinación **30 veces**.
  - Al finalizar guarda los tiempos de ejecución en archivos `.dat`.

### 🖥️ Entornos de ejecución

| Sistema          | Núcleos / Hilos | RAM    |
|------------------|------------------|--------|
| WSL              | Variable         | 3.8 MiB|
| Ubuntu (12)    | 4 hilos          | 11 GB  |
| Ubuntu (16)    | 8 hilos          | 15 GB  |
| Replit           | 8 hilos      | 64 GB  |

---

## 📊 Resultados esperados

Para cada ejecución se obtiene:

- Un archivo con los **tiempos de ejecución** por combinación (algoritmo + tamaño de matriz + número de hilos + sistema).
- Datos listos para análisis comparativo.

---

## 🧳 Cómo Ejecutar

```bash
incluir "chmod +x mmClasicaPosix mmClasicaFork mmClasicaOpenMP" en caso de usar archivos pre-compilados

gcc mmClasicaPosix.c mmInterfazPosix.c -o mmClasicaPosix -pthread
gcc mmClasicaFork.c mmInterfazFork.c -o mmClasicaFork
gcc mmClasicaOpenMP.c mmInterfazOpenMP.c -o mmClasicaOpenMP -fopenmp
/usr/bin/perl ./lanza.pl
