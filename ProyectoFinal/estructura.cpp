#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// ----- Estructura básica de una canción -----
struct Cancion {
    std::string artista;
    std::string titulo;
    std::string id;
    std::string genero;
    int anio;
    int popularidad;

    Cancion(const std::string& a, const std::string& t, const std::string& i, const std::string& g, int y, int p)
        : artista(a), titulo(t), id(i), genero(g), anio(y), popularidad(p) {}
};

// ----- Árbol Binario de Búsqueda -----
struct NodoArbol {
    Cancion cancion;
    NodoArbol* izquierda;
    NodoArbol* derecha;

    NodoArbol(const Cancion& c) : cancion(c), izquierda(nullptr), derecha(nullptr) {}
};

class ArbolBinario {
private:
    NodoArbol* raiz;

    void insertarNodo(NodoArbol*& nodo, const Cancion& cancion) {
        if (!nodo) {
            nodo = new NodoArbol(cancion);
        } else if (cancion.titulo < nodo->cancion.titulo) {
            insertarNodo(nodo->izquierda, cancion);
        } else {
            insertarNodo(nodo->derecha, cancion);
        }
    }

    void inOrden(NodoArbol* nodo) const {
        if (nodo) {
            inOrden(nodo->izquierda);
            std::cout << "- " << nodo->cancion.titulo << " - " << nodo->cancion.artista
                      << " (" << nodo->cancion.anio << ") Género: " << nodo->cancion.genero
                      << ", Popularidad: " << nodo->cancion.popularidad << "\n";
            inOrden(nodo->derecha);
        }
    }

    void liberarNodos(NodoArbol* nodo) {
        if (nodo) {
            liberarNodos(nodo->izquierda);
            liberarNodos(nodo->derecha);
            delete nodo;
        }
    }

public:
    ArbolBinario() : raiz(nullptr) {}

    ~ArbolBinario() {
        liberarNodos(raiz);
    }

    void agregarCancion(const Cancion& cancion) {
        insertarNodo(raiz, cancion);
    }

    void mostrarOrdenado() const {
        if (!raiz) {
            std::cout << "El árbol está vacío.\n";
        } else {
            inOrden(raiz);
        }
    }
};

// ----- Función para cargar canciones desde un archivo CSV -----
void cargarCancionesDesdeCSV(const std::string& archivo, ArbolBinario& arbol) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << archivo << "\n";
        return;
    }

    std::string linea;
    // Leer y descartar encabezado
    std::getline(file, linea);

    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string indice, artista, titulo, id, genero, temp;
        int anio = 0, popularidad = 0;

        try {
            std::getline(ss, indice, ',');   // Índice (descartado)
            std::getline(ss, artista, ','); // Nombre del artista
            std::getline(ss, titulo, ',');  // Nombre de la canción
            std::getline(ss, id, ',');      // ID de la canción
            std::getline(ss, temp, ',');    // Popularidad
            if (!temp.empty()) popularidad = std::stoi(temp);
            std::getline(ss, temp, ',');    // Año
            if (!temp.empty()) anio = std::stoi(temp);
            std::getline(ss, genero, ',');  // Género

            // Validar campos requeridos
            if (artista.empty() || titulo.empty() || id.empty() || genero.empty()) {
                std::cerr << "Línea inválida, se omitirá: " << linea << "\n";
                continue;
            }

            // Crear canción y agregar al árbol
            Cancion cancion(artista, titulo, id, genero, anio, popularidad);
            arbol.agregarCancion(cancion);
        } catch (const std::exception& e) {
            std::cerr << "Error procesando la línea, se omitirá: " << linea << "\n";
        }
    }

    std::cout << "Canciones cargadas desde el archivo: " << archivo << "\n";
}

// ----- Función Principal -----
int main() {
    ArbolBinario arbol;

    // Ruta del archivo CSV
    std::string archivoCSV = "spotify_data.csv";

    // Cargar canciones desde el CSV en el árbol binario
    cargarCancionesDesdeCSV(archivoCSV, arbol);

    // Mostrar canciones ordenadas por título
    std::cout << "\nCanciones ordenadas por título:\n";
    arbol.mostrarOrdenado();

    return 0;
}
