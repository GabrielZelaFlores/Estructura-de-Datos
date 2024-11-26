# Proyecto: Sistema de Lista de Reproducción de Canciones en C++ 🎵

## Integrantes del Proyecto

- Huamaní Vásquez Juan José
- Valdivia Vásquez Gian Pool
- Zela Flores Gabriel Frank

---

## Código Completo

```cpp
#include <iostream>
#include <string>

using namespace std;

// Clase para representar una canción
class Cancion {
public:
    string titulo;
    string artista;
    int duracion; // en segundos

    Cancion(string titulo, string artista, int duracion)
        : titulo(titulo), artista(artista), duracion(duracion) {}

    void mostrar() const {
        cout << "Título: " << titulo << ", Artista: " << artista << ", Duración: " << duracion << " segundos" << endl;
    }
};

// Nodo de la lista enlazada doble
class Nodo {
public:
    Cancion cancion;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(Cancion cancion) : cancion(cancion), siguiente(nullptr), anterior(nullptr) {}
};

// Clase para gestionar la lista de reproducción
class ListaReproduccion {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaReproduccion() : cabeza(nullptr), cola(nullptr) {}

    // Método para agregar una canción al final de la lista
    void agregarCancion(const Cancion& cancion) {
        Nodo* nuevoNodo = new Nodo(cancion);
        if (!cabeza) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
        cout << "Canción agregada: " << cancion.titulo << endl;
    }

    // Método para eliminar una canción por título
    void eliminarCancion(const string& titulo) {
        if (!cabeza) {
            cout << "La lista está vacía. No se puede eliminar." << endl;
            return;
        }

        Nodo* actual = cabeza;
        while (actual && actual->cancion.titulo != titulo) {
            actual = actual->siguiente;
        }

        if (!actual) {
            cout << "Canción no encontrada: " << titulo << endl;
        } else {
            if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
            if (actual->siguiente) actual->siguiente->anterior = actual->anterior;

            if (actual == cabeza) cabeza = actual->siguiente;
            if (actual == cola) cola = actual->anterior;

            delete actual;
            cout << "Canción eliminada: " << titulo << endl;
        }
    }

    // Método para mostrar todas las canciones en la lista
    void mostrarLista() const {
        if (!cabeza) {
            cout << "La lista de reproducción está vacía." << endl;
            return;
        }

        Nodo* actual = cabeza;
        while (actual) {
            actual->cancion.mostrar();
            actual = actual->siguiente;
        }
    }
};

// Función principal para probar la funcionalidad básica
int main() {
    ListaReproduccion lista;

    // Agregar canciones
    lista.agregarCancion(Cancion("Song 1", "Artist 1", 200));
    lista.agregarCancion(Cancion("Song 2", "Artist 2", 180));
    lista.agregarCancion(Cancion("Song 3", "Artist 3", 240));

    cout << "\nLista de Reproducción:" << endl;
    lista.mostrarLista();

    // Eliminar una canción
    cout << "\nEliminando 'Song 2'..." << endl;
    lista.eliminarCancion("Song 2");

    cout << "\nLista de Reproducción Actualizada:" << endl;
    lista.mostrarLista();

    return 0;
}
```

---

## Descripción

Este proyecto implementa una **lista de reproducción de canciones** en C++ utilizando una estructura de datos de lista doblemente enlazada. La lista permite gestionar canciones mediante operaciones básicas como agregar, eliminar y mostrar canciones en la lista de reproducción.

---

## Estructuras de Datos Utilizadas

### Lista Enlazada Doble
- **Función**: La lista enlazada doble permite agregar y eliminar canciones fácilmente y cambiar su orden sin necesidad de reorganizar toda la lista.
- **Uso en el Proyecto**: Cada canción se representa como un nodo de la lista enlazada doble, que contiene información como el título, el artista y la duración. Los nodos tienen punteros al nodo anterior y al siguiente, lo que permite un acceso eficiente en ambas direcciones.

### Árbol Binario de Búsqueda (BST)
- **Función**: Estos árboles permiten ordenar y buscar canciones de forma eficiente por atributos específicos, como popularidad o año de lanzamiento.
- **Uso en el Proyecto**: Aunque actualmente no está implementado, en futuras etapas del desarrollo los nodos del árbol podrían representar canciones ordenadas por un atributo específico.

### Array Dinámico
- **Función**: Almacena temporalmente las canciones, permitiendo generar vistas de la lista ordenadas según diferentes criterios, como popularidad o duración.
- **Uso en el Proyecto**: En futuras mejoras, el array se redimensionará dinámicamente para mostrar las canciones en una vista ordenada.

---

## Librerías Utilizadas

1. **`<iostream>`**: Para la entrada y salida de datos.
2. **`<string>`**: Para manejar textos, como el título y el artista de las canciones.
3. **`<vector>`** (potencial uso en mejoras futuras): Para gestionar temporalmente las canciones en diferentes vistas ordenadas.

---

## Estructura del Código

### Clases y Estructuras Principales

1. **Clase `Cancion`**: 
   Representa una canción con atributos de título, artista, y duración en segundos. Incluye un método `mostrar` para imprimir los detalles de la canción.

   ```cpp
   class Cancion {
   public:
       string titulo;
       string artista;
       int duracion;

       Cancion(string titulo, string artista, int duracion)
           : titulo(titulo), artista(artista), duracion(duracion) {}

       void mostrar() const {
           cout << "Título: " << titulo << ", Artista: " << artista << ", Duración: " << duracion << " segundos" << endl;
       }
   };
   ```

2. **Clase `Nodo`**: 
   Nodo de la lista doblemente enlazada, que contiene un objeto `Cancion` y punteros hacia el siguiente y el nodo anterior.

   ```cpp
   class Nodo {
   public:
       Cancion cancion;
       Nodo* siguiente;
       Nodo* anterior;

       Nodo(Cancion cancion) : cancion(cancion), siguiente(nullptr), anterior(nullptr) {}
   };
   ```

3. **Clase `ListaReproduccion`**: 
   Clase principal que gestiona la lista de reproducción. Permite agregar canciones, eliminarlas por título y mostrar la lista completa.

   ```cpp
   class ListaReproduccion {
   private:
       Nodo* cabeza;
       Nodo* cola;

   public:
       ListaReproduccion() : cabeza(nullptr), cola(nullptr) {}

       // Método para agregar una canción al final de la lista
       void agregarCancion(const Cancion& cancion) {
           Nodo* nuevoNodo = new Nodo(cancion);
           if (!cabeza) {
               cabeza = cola = nuevoNodo;
           } else {
               cola->siguiente = nuevoNodo;
               nuevoNodo->anterior = cola;
               cola = nuevoNodo;
           }
           cout << "Canción agregada: " << cancion.titulo << endl;
       }

       // Método para eliminar una canción por título
       void eliminarCancion(const string& titulo) {
           if (!cabeza) {
               cout << "La lista está vacía. No se puede eliminar." << endl;
               return;
           }

           Nodo* actual = cabeza;
           while (actual && actual->cancion.titulo != titulo) {
               actual = actual->siguiente;
           }

           if (!actual) {
               cout << "Canción no encontrada: " << titulo << endl;
           } else {
               if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
               if (actual->siguiente) actual->siguiente->anterior = actual->anterior;

               if (actual == cabeza) cabeza = actual->siguiente;
               if (actual == cola) cola = actual->anterior;

               delete actual;
               cout << "Canción eliminada: " << titulo << endl;
           }
       }

       // Método para mostrar todas las canciones en la lista
       void mostrarLista() const {
           if (!cabeza) {
               cout << "La lista de reproducción está vacía." << endl;
               return;
           }

           Nodo* actual = cabeza;
           while (actual) {
               actual->cancion.mostrar();
               actual = actual->siguiente;
           }
       }
   };
   ```

### Función Principal `main`

La función principal (`main`) demuestra la funcionalidad básica de la lista de reproducción:

1. **Agregar canciones** a la lista.
2. **Mostrar la lista de reproducción**.
3. **Eliminar una canción** por su título.
4. **Mostrar la lista de reproducción** nuevamente para ver los cambios.

---

## Ejecución del Programa

### Instrucciones de Ejecución

1. **Compilar el código** usando un compilador de C++:
   ```bash
   g++ main.cpp -o lista_reproduccion
   ```

2. **Ejecutar el programa**:
   ```bash
   ./lista_reproduccion
   ```

### Ejemplo de Salida

Al ejecutar el programa, la salida en consola será similar a:

```
Canción agregada: Song 1
Canción agregada: Song 2
Canción agregada: Song 3

Lista de Reproducción:
Título: Song 1, Artista: Artist 1, Duración: 200 segundos
Título: Song 2, Artista: Artist 2, Duración: 180 segundos
Título: Song 3, Artista: Artist 3, Duración: 240 segundos

Eliminando 'Song 2'...
Canción eliminada: Song 2

Lista de Reproducción Actualizada:
Título: Song 1, Artista: Artist 1, Duración: 200 segundos
Título: Song 3, Artista: Artist 3, Duración: 240 segundos
```

---

## Explicación de Funcionamiento

- **Agregar Canción**: Se añade un nodo nuevo al final de la lista. Si la lista está vacía, el nuevo nodo se convierte en la cabeza y la cola de la lista.
- **Eliminar Canción**: Se busca el nodo que contiene la canción por su título. Si se encuentra, se

 actualizan los punteros de los nodos adyacentes para mantener la integridad de la lista y se elimina el nodo.
- **Mostrar Lista**: Recorre todos los nodos de la lista desde la cabeza y muestra los detalles de cada canción.

---

## Posibles Mejoras

1. **Evitar duplicados**: Agregar control para evitar canciones con el mismo título.
2. **Reproducción en bucle**: Implementar una función que permita reproducir en un ciclo continuo las canciones.
```

### Informe del Proyecto PART2 : Sistema de Gestión de Canciones

---

### Resumen del Proyecto
El objetivo del proyecto es construir un sistema de gestión de canciones utilizando estructuras de datos avanzadas como una **Lista Doblemente Enlazada (DoublyLinkedList)**, un **Árbol AVL (AVLTree)** y una **Tabla Hash (HashTable)**. Cada estructura cumple un propósito específico: facilitar la manipulación, búsqueda y almacenamiento eficiente de datos relacionados con canciones. El sistema incluye la posibilidad de cargar canciones desde un archivo CSV, realizar operaciones CRUD (crear, leer, actualizar, eliminar), y mostrar los datos en diferentes estructuras.

---

### Estructuras Implementadas
A continuación, se describen las principales estructuras de datos utilizadas:

---

#### **1. Árbol AVL (AVLTree)** 
**Propósito**: Implementar un árbol de búsqueda binaria balanceado para realizar búsquedas eficientes en O(log n).

**Características**:
- Balancea automáticamente el árbol al realizar inserciones.
- Rotaciones simples y dobles para mantener el balance.
- Los nodos contienen información de la canción, un puntero a sus hijos izquierdo y derecho, y la altura del nodo.

```cpp
---
AVLTree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include "Song.h"
#include <iostream>

class AVLTree {
private:
    struct Node {
        Song song;
        Node* left;
        Node* right;
        int height;
        Node(const Song& s) : song(s), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* node);
    int balanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, const Song& song);

public:
    AVLTree() : root(nullptr) {}
    void insert(const Song& song);
};

#endif
---
```

---

#### **2. Lista Doblemente Enlazada (DoublyLinkedList)** 
**Propósito**: Manejar datos secuenciales de forma dinámica.

**Características**:
- Permite recorrer la lista en ambos sentidos (hacia adelante y hacia atrás).
- Operaciones principales:
  - **addSong**: Agrega canciones al final.
  - **removeSong**: Elimina una canción dado su ID.
  - **printAll**: Muestra las canciones en el orden de inserción.

```cpp
---
DoublyLinkedList.h
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Song.h"
#include <iostream>

class DoublyLinkedList {
private:
    struct Node {
        Song song;
        Node* next;
        Node* prev;
        Node(const Song& s) : song(s), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    void addSong(const Song& song);
    bool removeSong(const std::string& trackId);
    void printAll() const;
};

#endif
---
```

---

#### **3. Tabla Hash (HashTable)** 
**Propósito**: Implementar una tabla hash eficiente para realizar búsquedas de canciones por ID en O(1) en el mejor de los casos.

**Características**:
- Usa el ID de la canción como clave para calcular su posición en la tabla.
- Manejo de colisiones mediante **listas enlazadas** en cada bucket.
- Funcionalidades principales:
  - **insert**: Inserta una canción si no está duplicada.
  - **remove**: Elimina una canción dado su ID.
  - **find**: Busca y retorna una canción por su ID.

```cpp
---
HashTable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include "Song.h"

class HashTable {
private:
    static const int TABLE_SIZE = 10007;
    std::vector<std::list<Song>> table;
    int hash(const std::string& key) const;

public:
    HashTable() : table(TABLE_SIZE) {}
    void insert(const Song& song);
    bool remove(const std::string& trackId);
    Song* find(const std::string& trackId);
};

#endif
---
```

---

#### **4. Clase Song** 
**Propósito**: Representar una canción con todos sus atributos.

**Atributos**:
- ID de la canción.
- Nombre del artista.
- Nombre de la canción.
- Género, año, popularidad y duración.

```cpp
---
Song.h
#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
private:
    std::string trackId;
    std::string artistName;
    std::string trackName;
    std::string genre;
    int year;
    int popularity;
    int duration;

public:
    Song(const std::string& id, const std::string& artist, const std::string& track,
         const std::string& genre, int year, int popularity, int duration)
        : trackId(id), artistName(artist), trackName(track), genre(genre),
          year(year), popularity(popularity), duration(duration) {}

    const std::string& getTrackId() const;
    const std::string& getArtistName() const;
    const std::string& getTrackName() const;
    const std::string& getGenre() const;
    int getYear() const;
    int getPopularity() const;
    int getDuration() const;
};

#endif
---
```

---

### Carga de Canciones desde CSV
El archivo `main.cpp` incluye una función para cargar canciones desde un archivo CSV. Las canciones se agregan a las tres estructuras implementadas (Lista, Árbol y Tabla Hash).

```cpp
---
void loadSongsFromCSV(const std::string& filename, DoublyLinkedList& list,
                      HashTable& hashTable, AVLTree& avlTree) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo CSV.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, artist, track, genre;
        int year, popularity, duration;
        std::getline(ss, id, ',');
        std::getline(ss, artist, ',');
        std::getline(ss, track, ',');
        std::getline(ss, genre, ',');
        ss >> year >> popularity >> duration;

        Song song(id, artist, track, genre, year, popularity, duration);
        list.addSong(song);
        hashTable.insert(song);
        avlTree.insert(song);
    }
    file.close();
}
---
```

---

### Interfaz de Usuario
El programa incluye un menú interactivo con las siguientes opciones:
1. **Agregar canción**.
2. **Eliminar canción**.
3. **Buscar canción por ID**.
4. **Mostrar todas las canciones**.
5. **Salir del programa**.

```cpp
---
main.cpp
int main() {
    DoublyLinkedList playlist;
    HashTable hashTable;
    AVLTree avlTree;

    loadSongsFromCSV("spotify_data.csv", playlist, hashTable, avlTree);

    int option;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Agregar canción\n";
        std::cout << "2. Eliminar canción\n";
        std::cout << "3. Buscar canción\n";
        std::cout << "4. Mostrar canciones\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        switch (option) {
            case 1:
                // Implementación de agregar canción
                break;
            case 2:
                // Implementación de eliminar canción
                break;
            case 3:
                // Implementación de buscar canción
                break;
            case 4:
                // Implementación de mostrar canciones
                break;
            case 5:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (option != 5);

    return 0;
}
---
```

---

### Conclusión
El sistema implementa estructuras de datos modernas para manejar un conjunto de canciones de manera eficiente, soportando operaciones clave como inserción, eliminación y búsqueda. Es escalable y puede manejar grandes volúmenes de datos gracias a la Tabla Hash y el Árbol AVL.

### Posibles Mejoras
1. Implementar serialización para guardar los datos en archivos persistentes.
2. Agregar pruebas unitarias para garantizar la funcionalidad.
3. Optimizar la búsqueda en el menú para interactuar con estructuras específicas.


