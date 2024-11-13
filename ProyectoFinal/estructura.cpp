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
