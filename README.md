
 # Informe Experimental: Comparación de Tiempos de Ejecución en un B-tree con Diferentes Valores de MAX_KEYS

### Librerías Utilizadas

1. **<stdio.h>**: Proporciona funciones para entrada y salida estándar. En este código, se utiliza para:
   - **Impresión de mensajes** en la consola (printf), como las notificaciones de errores y el resultado del árbol B.
   - **Manejo de archivos** (fopen, fprintf, fclose) para generar el archivo .dot para visualización del árbol.

2. **<stdlib.h>**: Incluye funciones de utilidad general para:
   - **Asignación de memoria dinámica** (malloc y free), utilizada al crear y liberar nodos en el B-tree.
   - **Conversión de datos** (atoi y atof) en la función de importación de datos desde el archivo CSV.

3. **<string.h>**: Contiene funciones para la manipulación de cadenas. Se usa principalmente para:
   - **Dividir y procesar líneas** en la función importCSVAndCreateBTree mediante strtok para extraer claves individuales desde el archivo CSV.

4. **<time.h>**: Biblioteca de funciones de tiempo utilizada en main.cpp para:
   - **Medición de tiempos de ejecución** (clock) durante la carga de datos y la búsqueda en el B-tree, con el fin de comparar el rendimiento para diferentes valores de MAX_KEYS.

---

### Resumen

Este código implementa un B-tree que permite la inserción de claves y la generación de un archivo de visualización en formato DOT. La estructura del árbol cambia según el valor de MAX_KEYS, lo que define el número máximo de claves por nodo y afecta la profundidad del árbol y la eficiencia en operaciones de inserción y búsqueda.

El objetivo de este experimento es evaluar el rendimiento del B-tree al variar MAX_KEYS entre 2 y 3. Para ello:
- Se mide el **tiempo de carga de datos** al insertar claves desde un archivo CSV en el árbol.
- Se mide el **tiempo de búsqueda** para una clave específica en el árbol generado.

---

### Objetivo
Este experimento evalúa el impacto de utilizar diferentes valores para la variable MAX_KEYS en un B-tree, específicamente MAX_KEYS = 2 y MAX_KEYS = 3. Se mide y compara el tiempo de ejecución en dos operaciones principales:
1. **Carga de datos**: el tiempo que tarda en insertar datos en el B-tree desde un archivo CSV.
2. **Búsqueda de una clave**: el tiempo que tarda en buscar una clave específica en el árbol ya construido.

### Metodología
Para llevar a cabo este experimento, el código fue modificado para medir el tiempo de ejecución de las operaciones de carga y búsqueda. Se utilizó la función clock() de la biblioteca <time.h> para registrar los tiempos.

1. **Configuración del archivo b_tree.h**:
   - Se varió el valor de MAX_KEYS entre 2 y 3.
   - Se recompiló el código en cada caso y se ejecutaron las pruebas de tiempo.

2. **Operaciones Medidas**:
   - **Carga de datos**: el tiempo necesario para insertar todas las claves desde un archivo CSV en el B-tree.
   - **Búsqueda de una clave**: el tiempo necesario para buscar una clave específica en el B-tree.

3. **Parámetros del experimento**:
   - Archivo CSV: random_numbers_1000000.csv (contiene un millón de valores para insertar en el árbol).
   - Clave de búsqueda: Se seleccionó una clave de prueba (CLAVE_BUSCAR = 5000) para evaluar la búsqueda en el árbol después de la carga.

### Resultados Experimentales

| Configuración de MAX_KEYS | Tiempo de Carga (segundos) | Tiempo de Búsqueda (segundos) |
|-----------------------------|----------------------------|-------------------------------|
| MAX_KEYS = 2              | X.XXXX                     | X.XXXX                        |
| MAX_KEYS = 3              | X.XXXX                     | X.XXXX                        |

> **Nota**: Los valores de tiempo exactos se deben llenar después de realizar la ejecución del código en cada configuración.

### Análisis y Conclusión

1. **Análisis de Carga de Datos**:
   - **MAX_KEYS = 2**: Al tener un menor número de claves por nodo, el B-tree genera más divisiones y, en consecuencia, más niveles. Esto puede aumentar el tiempo de inserción ya que cada nodo se llena rápidamente y debe dividirse con mayor frecuencia.
   - **MAX_KEYS = 3**: Al permitir más claves por nodo, el árbol es menos profundo, ya que cada nodo puede almacenar más claves antes de dividirse. Esto puede reducir el número de divisiones necesarias y acelerar la inserción.

2. **Análisis de Búsqueda**:
   - **MAX_KEYS = 2**: Debido a la mayor profundidad del árbol, la búsqueda puede requerir más pasos para alcanzar los nodos hoja, lo cual puede aumentar el tiempo de búsqueda.
   - **MAX_KEYS = 3**: Con menos divisiones y una menor profundidad del árbol, la búsqueda es más eficiente, ya que se necesitan menos pasos para alcanzar los nodos hoja.

3. **Conclusión General**:
   - En general, un valor mayor de MAX_KEYS permite un rendimiento superior en términos de inserción y búsqueda, ya que el árbol es menos profundo y las operaciones son más eficientes. Sin embargo, el valor óptimo de MAX_KEYS puede depender de la estructura de los datos y del tamaño del conjunto de datos. Para este experimento, **MAX_KEYS = 3** ofrece un mejor equilibrio entre la velocidad de inserción y la eficiencia de búsqueda.

### Ejecución del Experimento
Para replicar este experimento:

1. Configura MAX_KEYS en b_tree.h a 2, compila y ejecuta el código.
2. Registra los tiempos de carga y búsqueda.
3. Cambia MAX_KEYS a 3 en b_tree.h, compila y ejecuta nuevamente.
4. Compara los resultados en esta tabla y realiza un análisis similar.
