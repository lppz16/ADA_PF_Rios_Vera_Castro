# ADA_PF_Rios_Vera_Castro

Proyecto final de **Análisis y Diseño de Algoritmos (ADA)** aplicado sobre un dataset real de telecomunicaciones utilizando distintos paradigmas algorítmicos.


## **Integrantes:**
- Guadalupe Castro 
- Tomas Vera
- Yan Frank Ríos López

| Apellido | Rol |
|---|---|
| Rios | Desarrollo e integración de algoritmos |
| Vera | Manejo de datos y validaciones |
| Castro | Documentación, pruebas y análisis |

---
### Librerías utilizadas

- `<vector>`
- `<string>`
- `<fstream>`
- `<sstream>`
- `<algorithm>`
- `<chrono>`
- `<cmath>`

---

## Herramientas Utilizadas

### Desarrollo:

- C++17
- g++
- Visual Studio Code

---
  
## Objetivo general 

Desarrollar una solucion modular, aplicando distintos paradigmas de anlisis y diseño de algoritmos sobre un dataset real de comunicaciones.

El proyecto integra:

- Divide y vencerás
- Algoritmos codiciosos
- Programación dinámica
- Estructuras eficientes
- Análisis de complejidad

---

## Descripción General:

El sistema trabaja con el dataset:

`WA_Fn-UseC_-Telco-Customer-Churn.csv`

el cual contiene información de clientes de una empresa de telecomunicaciones, incluyendo:

- Tiempo de permanencia (`tenure`)
- Cobro mensual (`MonthlyCharges`)
- Cobro total (`TotalCharges`)
- Estado de abandono (`Churn`)

El proyecto está dividido en tres grandes módulos:

1. **Divide y Vencerás**
   - MergeSort
   - Búsqueda Binaria

2. **Algoritmos Codiciosos**
   - Construcción de grafo
   - Kruskal
   - Union-Find

3. **Programación Dinámica**
   - Problema de la Mochila 0/1

  ---

  # Funcionalidades

- Lectura y parseo de CSV
- Ordenamiento de clientes por `tenure`
- Búsqueda binaria eficiente
- Construcción de un grafo completo
- Obtención de un MST usando Kruskal
- Optimización mediante Mochila 0/1
- Medición de tiempos de ejecución

---

  # Estructura del Proyecto

```txt
ADA_PF_Rios_Vera_Castro-main/
│
├── data/
│   └── WA_Fn-UseC_-Telco-Customer-Churn.csv
│
├── results/
│   ├── asignacion_bw.txt
│   ├── busquedas_A.txt
│   ├── mst_red.txt
│   └── solicitudes_ordenadas.csv
│
├── src/
│   ├── binary_search.cpp
│   ├── binary_search.hpp
│   ├── graph.cpp
│   ├── graph.hpp
│   ├── knapsack.cpp
│   ├── knapsack.hpp
│   ├── kruskal.cpp
│   ├── kruskal.hpp
│   ├── main.cpp
│   ├── mergesort.cpp
│   ├── mergesort.hpp
│   ├── parser.cpp
│   └── parser.hpp
│
└── ada_pf
```
---
# Pipeline General

```txt
CSV
 ↓
Parser
 ↓
MergeSort
 ↓
Binary Search
 ↓
Resultados
```

Pipeline adicional:

```txt
Dataset
 ↓
Construcción de Grafo
 ↓
Kruskal
 ↓
MST
```

Y para optimización:

```txt
Clientes activos
 ↓
Mochila 0/1
 ↓
Asignación óptima
```
---
# Complejidades

| Algoritmo | Complejidad |
|---|---|
| MergeSort | O(n log n) |
| Binary Search | O(log n) |
| Kruskal | O(E log E) |
| Union-Find | O(α(n)) |
| Mochila 0/1 | O(nW) |

---

# Compilación

## Linux / g++

```bash
g++ src/*.cpp -std=c++17 -o ada_pf
```

---
# Ejecución

```bash
./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv
```
---

# Resultados Generados

El programa genera archivos en la carpeta:

```txt
results/
```

Incluyendo:

- `solicitudes_ordenadas.csv`
- `busquedas_A.txt`
- `mst_red.txt`
- `asignacion_bw.txt`

---

# Ejemplo de Salida

```txt
Registros cargados: 7043

MergeSort completado
Busqueda tenure = 72

Peso total MST: 3542

Valor óptimo mochila: 12870
```

---

# Tecnologías Utilizadas

- C++17
- STL
- g++
- Visual Studio Code

---

# Conclusión

El proyecto integra múltiples paradigmas de diseño de algoritmos sobre un problema real de análisis de datos, combinando eficiencia, modularidad y optimización computacional.





















