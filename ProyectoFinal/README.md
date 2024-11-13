### Informe de Avance del Proyecto: Gestor de Lista de Reproducción de Canciones

## Estructuras de Datos
- Lista Enlazada Doble:
Función: Utilizaremos una lista enlazada doble para almacenar las canciones. Este tipo de estructura permite agregar y eliminar canciones fácilmente y cambiar su orden sin reordenar toda la lista.
Uso en el Proyecto: Cada canción será un nodo de la lista enlazada doble, conteniendo información básica como título, artista y duración. Los nodos de la lista enlazada tendrán punteros al nodo anterior y al siguiente, permitiendo un acceso eficiente en ambas direcciones.

- Árbol Binario de Búsqueda (BST) o Árbol AVL (opcional):
Función: Permite ordenar y buscar canciones por atributos específicos como popularidad o año de lanzamiento.
Uso en el Proyecto: Los nodos del árbol representarán canciones, ordenadas por un atributo específico (a implementar en etapas futuras).

- Vector Dinámico:
Función: Para almacenar las canciones de forma temporal y permitir vistas ordenadas por diferentes criterios (popularidad, duración, etc.).
Uso en el Proyecto: Un vector que se redimensiona dinámicamente para almacenar las canciones según la vista seleccionada.

## Librerías
iostream: Para entrada y salida de datos.
string: Para manejar texto (título, artista, etc.).
cstdlib y ctime (para reproducción aleatoria, si se implementa).
vector: Para el manejo temporal de canciones ordenadas (opcional).

## Descripción del Código
El código inicial se compone de tres clases:
Clase Cancion: Representa una canción con atributos básicos y un método mostrar para imprimir la información.
Clase Nodo y ListaReproduccion: Implementa la lista enlazada doble. Contiene métodos para agregar y eliminar canciones y mostrar la lista.
Función Principal: Permite agregar y eliminar canciones, y visualizar la lista de reproducción.
