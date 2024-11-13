# Gestor de Lista de Reproducción de Canciones 🎵

Este proyecto es un gestor de listas de reproducción de canciones desarrollado en C++, diseñado para almacenar, organizar y manipular canciones utilizando varias estructuras de datos. Implementa una lista enlazada doble para gestionar dinámicamente la lista de reproducción, además de un árbol binario de búsqueda (BST) o AVL para búsquedas y ordenamientos opcionales.

## Estructuras de Datos Utilizadas

### Lista Enlazada Doble
- **Función**: La lista enlazada doble permite agregar y eliminar canciones fácilmente y cambiar su orden sin necesidad de reorganizar la lista completa.
- **Uso en el Proyecto**: Cada canción se representa como un nodo de la lista enlazada doble, con información como el título, artista y duración. Los nodos tienen punteros al nodo anterior y al siguiente, lo que permite un acceso eficiente en ambas direcciones.

### Árbol Binario de Búsqueda (BST) o Árbol AVL (opcional)
- **Función**: Estos árboles permiten ordenar y buscar canciones de forma eficiente por atributos específicos, como popularidad o año de lanzamiento.
- **Uso en el Proyecto**: En futuras etapas del desarrollo, los nodos del árbol representarán canciones, ordenadas por un atributo específico.

### Vector Dinámico
- **Función**: Almacena temporalmente las canciones, permitiendo generar vistas de la lista ordenadas según diferentes criterios, como popularidad o duración.
- **Uso en el Proyecto**: Este vector se redimensiona dinámicamente para mostrar las canciones en una vista ordenada.

## Librerías Utilizadas

- **iostream**: Para la entrada y salida de datos.
- **string**: Para manejar textos como el título y el artista.
- **cstdlib** y **ctime**: Se utilizan para implementar la reproducción aleatoria de canciones, si se decide implementar esta función.
- **vector**: Para el manejo temporal de las canciones en diferentes vistas ordenadas.

## Descripción del Código

El proyecto se compone de las siguientes clases:

### Clase `Cancion`
Representa una canción, con atributos básicos y un método `mostrar` que imprime la información de la canción.

### Clase `Nodo` y `ListaReproduccion`
Implementa la lista enlazada doble. Proporciona métodos para agregar, eliminar y mostrar las canciones en la lista de reproducción.

### Función Principal
La función principal permite:
- Agregar y eliminar canciones.
- Visualizar la lista de reproducción.

