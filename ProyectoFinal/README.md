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
