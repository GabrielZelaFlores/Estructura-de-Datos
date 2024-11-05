
# Informe Experimental: Comparación de Tiempos de Ejecución en un B-tree con Diferentes Valores de `MAX_KEYS`

Integrantes:

-Huamaní Vásquez Juan José
-Valdivia Vásquez Gian Pool
-Zela Flores Gabriel Frank

### Librerías Utilizadas

1. **`<stdio.h>`**: Proporciona funciones para entrada y salida estándar. En este código, se utiliza para:
   - **Impresión de mensajes** en la consola (`printf`), como las notificaciones de errores y el resultado del árbol B.
   - **Manejo de archivos** (`fopen`, `fprintf`, `fclose`) para generar el archivo `.dot` para visualización del árbol.

2. **`<stdlib.h>`**: Incluye funciones de utilidad general para:
   - **Asignación de memoria dinámica** (`malloc` y `free`), utilizada al crear y liberar nodos en el B-tree.
   - **Conversión de datos** (`atoi` y `atof`) en la función de importación de datos desde el archivo CSV.

3. **`<string.h>`**: Contiene funciones para la manipulación de cadenas. Se usa principalmente para:
   - **Dividir y procesar líneas** en la función `importCSVAndCreateBTree` mediante `strtok` para extraer claves individuales desde el archivo CSV.

4. **`<time.h>`**: Biblioteca de funciones de tiempo utilizada en `main.cpp` para:
   - **Medición de tiempos de ejecución** (`clock`) durante la carga de datos y la búsqueda en el B-tree, con el fin de comparar el rendimiento para diferentes valores de `MAX_KEYS`.

5. **Estructuras y Funciones Principales para el B-tree**:
   - **`btreeNode`**: Representa el nodo del B-tree, que contiene las claves y punteros a sus nodos hijos.
   - **`insert`**: Función principal para insertar una clave en el árbol B. Si el nodo raíz está lleno, llama a `splitChild`.
   - **`splitChild`**: Divide un nodo lleno en dos nodos, redistribuyendo las claves y ajustando punteros para mantener la estructura del B-tree.
   - **`insertNonFull`**: Inserta una clave en un nodo que no está lleno. Este es un subproceso de `insert`.
   - **`insertkey`**: Añade una clave en el lugar correcto dentro de un nodo.
   - **`printInOrder`**: Función que imprime el árbol en orden para visualizar la estructura actual del B-tree.

---

### Resumen

Este código implementa un B-tree que permite la inserción de claves y la generación de un archivo de visualización en formato DOT. La estructura del árbol cambia según el valor de `MAX_KEYS`, lo que define el número máximo de claves por nodo y afecta la profundidad del árbol y la eficiencia en operaciones de inserción y búsqueda.

El objetivo de este experimento es evaluar el rendimiento del B-tree al variar `MAX_KEYS` entre 3 , 4 y 5. Para ello:
- Se mide el **tiempo de carga de datos** al insertar claves desde un archivo CSV en el árbol.
- Se mide el **tiempo de búsqueda** para una clave específica en el árbol generado.

---

### Objetivo
Este experimento evalúa el impacto de utilizar diferentes valores para la variable `MAX_KEYS` en un B-tree, específicamente `MAX_KEYS = 3`, `MAX_KEYS = 4` y `MAX_KEYS = 5`. Se mide y compara el tiempo de ejecución en dos operaciones principales:
1. **Carga de datos**: el tiempo que tarda en insertar datos en el B-tree desde un archivo CSV.
2. **Búsqueda de una clave**: el tiempo que tarda en buscar una clave específica en el árbol ya construido.

### Metodología
Para llevar a cabo este experimento, el código fue modificado para medir el tiempo de ejecución de las operaciones de carga y búsqueda. Se utilizó la función `clock()` de la biblioteca `<time.h>` para registrar los tiempos.

### Visualización del B-tree

El siguiente archivo `.dot` permite la visualización de la estructura del B-tree utilizado en este experimento. Este archivo define los nodos y conexiones del árbol, y puede renderizarse usando herramientas de visualización como Graphviz. La estructura del árbol varía según el valor de `MAX_KEYS`, afectando la profundidad y distribución de las claves.


```dot
digraph BTree {
    node [shape=record];
    node0 [label="<f0>56 | <f1>"];
    node1 [label="<f0>19 | <f1> | <f2>40 | <f3>"];
    node2 [label="<f0>3 | <f1> | <f2>6 | <f3> | <f4>12 | <f5> | <f6>15 | <f7>"];
    node3 [label="<f0>0 | <f1> | <f2>1 | <f3> | <f4>2 | <f5>"];
    node2:f0 -> node3:f0;
    node4 [label="<f0>4 | <f1> | <f2>5 | <f3>"];
    node2:f1 -> node4:f0;
    node5 [label="<f0>7 | <f1> | <f2>8 | <f3> | <f4>9 | <f5> | <f6>10 | <f7> | <f8>11 | <f9>"];
    node2:f3 -> node5:f0;
    node6 [label="<f0>13 | <f1> | <f2>14 | <f3>"];
    node2:f5 -> node6:f0;
    node7 [label="<f0>16 | <f1> | <f2>17 | <f3> | <f4>18 | <f5>"];
    node2:f7 -> node7:f0;
    node1:f0 -> node2:f0;
    node8 [label="<f0>25 | <f1> | <f2>29 | <f3> | <f4>32 | <f5> | <f6>37 | <f7>"];
    node9 [label="<f0>20 | <f1> | <f2>21 | <f3> | <f4>22 | <f5> | <f6>23 | <f7> | <f8>24 | <f9>"];
    node8:f0 -> node9:f0;
    node10 [label="<f0>26 | <f1> | <f2>27 | <f3> | <f4>28 | <f5>"];
    node8:f1 -> node10:f0;
    node11 [label="<f0>30 | <f1> | <f2>31 | <f3>"];
    node8:f3 -> node11:f0;
    node12 [label="<f0>33 | <f1> | <f2>34 | <f3> | <f4>35 | <f5> | <f6>36 | <f7>"];
    node8:f5 -> node12:f0;
    node13 [label="<f0>38 | <f1> | <f2>39 | <f3>"];
    node8:f7 -> node13:f0;
    node1:f1 -> node8:f0;
    node14 [label="<f0>44 | <f1> | <f2>48 | <f3> | <f4>53 | <f5>"];
    node15 [label="<f0>41 | <f1> | <f2>42 | <f3> | <f4>43 | <f5>"];
    node14:f0 -> node15:f0;
    node16 [label="<f0>45 | <f1> | <f2>46 | <f3> | <f4>47 | <f5>"];
    node14:f1 -> node16:f0;
    node17 [label="<f0>49 | <f1> | <f2>50 | <f3> | <f4>51 | <f5> | <f6>52 | <f7>"];
    node14:f3 -> node17:f0;
    node18 [label="<f0>54 | <f1> | <f2>55 | <f3>"];
    node14:f5 -> node18:f0;
    node1:f3 -> node14:f0;
    node0:f0 -> node1:f0;
    node19 [label="<f0>69 | <f1> | <f2>84 | <f3>"];
    node20 [label="<f0>61 | <f1> | <f2>64 | <f3>"];
    node21 [label="<f0>57 | <f1> | <f2>58 | <f3> | <f4>59 | <f5> | <f6>60 | <f7>"];
    node20:f0 -> node21:f0;
    node22 [label="<f0>62 | <f1> | <f2>63 | <f3>"];
    node20:f1 -> node22:f0;
    node23 [label="<f0>65 | <f1> | <f2>66 | <f3> | <f4>67 | <f5> | <f6>68 | <f7>"];
    node20:f3 -> node23:f0;
    node19:f0 -> node20:f0;
    node24 [label="<f0>73 | <f1> | <f2>76 | <f3> | <f4>80 | <f5>"];
    node25 [label="<f0>70 | <f1> | <f2>71 | <f3> | <f4>72 | <f5>"];
    node24:f0 -> node25:f0;
    node26 [label="<f0>74 | <f1> | <f2>75 | <f3>"];
    node24:f1 -> node26:f0;
    node27 [label="<f0>77 | <f1> | <f2>78 | <f3> | <f4>79 | <f5>"];
    node24:f3 -> node27:f0;
    node28 [label="<f0>81 | <f1> | <f2>82 | <f3> | <f4>83 | <f5>"];
    node24:f5 -> node28:f0;
    node19:f1 -> node24:f0;
    node29 [label="<f0>88 | <f1> | <f2>91 | <f3> | <f4>95 | <f5>"];
    node30 [label="<f0>85 | <f1> | <f2>86 | <f3> | <f4>87 | <f5>"];
    node29:f0 -> node30:f0;
    node31 [label="<f0>89 | <f1> | <f2>90 | <f3>"];
    node29:f1 -> node31:f0;
    node32 [label="<f0>92 | <f1> | <f2>93 | <f3> | <f4>94 | <f5>"];
    node29:f3 -> node32:f0;
    node33 [label="<f0>96 | <f1> | <f2>97 | <f3> | <f4>98 | <f5> | <f6>99 | <f7>"];
    node29:f5 -> node33:f0;
    node19:f3 -> node29:f0;
    node0:f1 -> node19:f0;
}
```
### Diagrama

![Diagrama de Graphviz](https://github.com/GabrielZelaFlores/Estructura-de-Datos/raw/main/graphviz.svg)

1. **Configuración del archivo `b_tree.h`**:
   - Se varió el valor de `MAX_KEYS` entre 3, 4 y 5.
   - Se recompiló el código en cada caso y se ejecutaron las pruebas de tiempo.

2. **Operaciones Medidas**:
   - **Carga de datos**: el tiempo necesario para insertar todas las claves desde un archivo CSV en el B-tree.
   - **Búsqueda de una clave**: el tiempo necesario para buscar una clave específica en el B-tree.

3. **Parámetros del experimento**:
   - Archivo CSV: `random_numbers_1000000.csv` (contiene un millón de valores para insertar en el árbol).
   - Clave de búsqueda: Se seleccionó una clave de prueba (`CLAVE_BUSCAR = 5000`) para evaluar la búsqueda en el árbol después de la carga.

### Resultados Experimentales

| Configuración de `N° LLAVES` | Tiempo de Búsqueda (clave existe) (nanosegundos) | Tiempo de Búsqueda (clave no existe) (nanosegundos) |
|-----------------------------|---------------------------------------------------|-----------------------------------------------------|
| `N° LLAVES = 3`             | 983.9                                            | 897                                                 |
| `N° LLAVES = 4`             | 744.1                                            | 793                                                 |
| `N° LLAVES = 5`             | 414.7                                            | 654.9                                               |

> **Análisis de Resultados**:

1. **Búsqueda de Claves Existentes**:
   - **`N° LLAVES = 3`**: La búsqueda de una clave que existe en el árbol tarda un promedio de **983.9 nanosegundos**. Este es el tiempo más alto registrado entre las configuraciones de llaves, probablemente debido a la mayor profundidad del árbol al tener menos claves por nodo.
   - **`N° LLAVES = 4`**: Con cuatro claves por nodo, el tiempo disminuye a **744.1 nanosegundos**, lo que sugiere que el árbol es menos profundo y se requiere un menor número de operaciones para encontrar la clave.
   - **`N° LLAVES = 5`**: El tiempo de búsqueda baja aún más a **414.7 nanosegundos**, indicando una mejora significativa en la eficiencia al aumentar el número de claves por nodo. La menor profundidad del árbol permite alcanzar las claves con menos pasos.

2. **Búsqueda de Claves No Existentes**:
   - **`N° LLAVES = 3`**: Para claves que no existen en el árbol, el tiempo de búsqueda promedio es de **897 nanosegundos**. Aunque no se encuentra la clave, el árbol aún se recorre hasta los nodos hoja, resultando en un tiempo de búsqueda elevado.
   - **`N° LLAVES = 4`**: Al permitir cuatro claves por nodo, el tiempo de búsqueda para una clave inexistente se reduce a **793 nanosegundos**, lo que refleja una mejora debido a la estructura menos profunda del árbol.
   - **`N° LLAVES = 5`**: Con cinco claves por nodo, el tiempo baja a **654.9 nanosegundos**. Este es el tiempo más bajo entre las configuraciones probadas, sugiriendo que la eficiencia mejora conforme disminuye la profundidad del árbol.

> **Comparación y Observaciones Relevantes**:
   - **Profundidad y Eficiencia**: La reducción en la profundidad del árbol al aumentar `N° LLAVES` disminuye tanto el tiempo de búsqueda para claves existentes como para claves inexistentes.
   - **Rendimiento Óptimo en Búsquedas**: La configuración de `N° LLAVES = 5` demuestra ser la más eficiente, mostrando que un mayor número de claves por nodo reduce la cantidad de operaciones necesarias y, por ende, el tiempo de búsqueda.
   - **Impacto en Inserciones**: Aunque este experimento se centra en la búsqueda, una mayor cantidad de claves por nodo (`N° LLAVES = 5`) puede también mejorar el rendimiento de las inserciones, dado que se requerirían menos divisiones de nodos. Sin embargo, esto depende de las operaciones realizadas sobre el árbol.

> **Conclusión**:
   - Al aumentar el número de llaves por nodo (`N° LLAVES`), el tiempo de búsqueda se reduce tanto para claves existentes como para claves no existentes en el árbol.
   - La configuración de `N° LLAVES = 5` ofrece el mejor rendimiento, lo que sugiere que el árbol, al ser menos profundo, permite una búsqueda más rápida al requerir menos comparaciones por nodo.




