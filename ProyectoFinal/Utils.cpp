#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>


int getValidatedOption(int min, int max) {
    int option;
    while (true) {
        std::cout << "Ingrese una opción (" << min << " - " << max << "): ";
        std::cin >> option;

        if (std::cin.fail() || option < min || option > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor, intente de nuevo.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return option;
        }
    }
}

void loadSongsFromCSV(const std::string& filename, DoublyLinkedList& list,
                      HashTable& hashTable, AVLTree& avlTree) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo CSV.\n";
        return;
    }

    std::string line;
    std::getline(file, line); // Leer encabezado y descartarlo

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string temp; // Para datos que se deben saltar
        std::string id, artist, track, genre, yearStr, popularityStr, durationStr;

        // Función lambda para manejar comillas
        

auto readField = [](std::stringstream& stream) {
    std::string field;
    if (stream.peek() == '"') { // Si el campo empieza con comillas
        stream.get(); // Quitar la comilla inicial
        std::getline(stream, field, '"'); // Leer hasta la comilla de cierre

        // Procesar el resto del contenido si hay más comillas dobles dobles
        while (stream.peek() == '"') {
            stream.get(); // Quitar la comilla adicional
            std::string temp;
            std::getline(stream, temp, '"'); // Leer hasta la siguiente comilla
            field += "\"" + temp; // Concatenar el contenido
        }

        stream.get(); // Quitar la coma que sigue después de las comillas
    } else {
        std::getline(stream, field, ','); // Leer normalmente
    }
    return field;
};
        // Leer y saltar la primera columna (número de canción)
        readField(ss);

        // Leer columnas relevantes
        artist = readField(ss);
        track = readField(ss);
        id = readField(ss); // Este es el track_id
        popularityStr = readField(ss);
        yearStr = readField(ss);
        genre = readField(ss);

        // Saltar columnas no necesarias
        for (int i = 0; i < 11; ++i) {
            readField(ss);
        }

        // Leer la duración (última columna relevante)
        durationStr = readField(ss);

        // Convertir columnas numéricas a enteros
        try {
            int year = std::stoi(yearStr);
            int popularity = std::stoi(popularityStr);
            int duration = std::stoi(durationStr);

            // Crear objeto Song y agregarlo a las estructuras
            Song song(id, artist, track, genre, year, popularity, duration);
            list.addSong(song);
            hashTable.insert(song);
            avlTree.insert(song);
        } catch (const std::exception& e) {
            std::cerr << "Error al procesar la línea: " << line << "\n";
            std::cerr << "Detalles: " << e.what() << "\n";
        }
    }

    file.close();
}

void displaySorted(DoublyLinkedList& list, const std::string& criteria, bool ascending) {
    if (criteria == "original") {
        // Mostrar canciones en el orden original de la lista doblemente enlazada
        if (ascending) {
            list.printAll(); // Orden normal: inicio a fin
        } else {
            list.printReverse(); // Orden inverso: fin a inicio
        }
        return;
    }

    // Convertir la lista a un vector para facilitar el manejo
    std::vector<Song> songs = list.toVector();

    // Si el criterio es "genero", solicita al usuario el género para filtrar
    if (criteria == "genero") {
        std::string genre;
        std::cout << "Ingrese el género para filtrar: ";
        std::cin.ignore(); // Limpiar el buffer
        std::getline(std::cin, genre);

        // Filtrar las canciones por género
        songs.erase(std::remove_if(songs.begin(), songs.end(),
                                   [&](const Song& song) { return song.getGenre() != genre; }),
                    songs.end());

        if (songs.empty()) {
            std::cout << "No se encontraron canciones del género \"" << genre << "\".\n";
            return;
        }

        // Ordenar automáticamente alfabéticamente por nombre de canción
        std::sort(songs.begin(), songs.end(), [&](const Song& a, const Song& b) {
            return ascending ? a.getTrackName() < b.getTrackName() : a.getTrackName() > b.getTrackName();
        });

        // Mostrar las canciones filtradas y ordenadas alfabéticamente
        std::cout << "Canciones del género \"" << genre << "\" (ordenadas alfabéticamente):\n";
        for (const auto& song : songs) {
            std::cout << song.getTrackName() << " - " << song.getArtistName()
                      << " (Popularidad: " << song.getPopularity()
                      << ", Duración: " << song.getDuration() << " ms)\n";
        }
        return;
    }

    // Ordenar según el criterio especificado
    if (criteria == "popularidad") {
        std::sort(songs.begin(), songs.end(), [&](const Song& a, const Song& b) {
            return ascending ? a.getPopularity() < b.getPopularity() : a.getPopularity() > b.getPopularity();
        });
    } else if (criteria == "año") {
        std::sort(songs.begin(), songs.end(), [&](const Song& a, const Song& b) {
            return ascending ? a.getYear() < b.getYear() : a.getYear() > b.getYear();
        });
    } else if (criteria == "duracion") {
        std::sort(songs.begin(), songs.end(), [&](const Song& a, const Song& b) {
            return ascending ? a.getDuration() < b.getDuration() : a.getDuration() > b.getDuration();
        });
    } else if (criteria == "alfabetico") {
        std::sort(songs.begin(), songs.end(), [&](const Song& a, const Song& b) {
            return ascending ? a.getTrackName() < b.getTrackName() : a.getTrackName() > b.getTrackName();
        });
    }

    // Mostrar las canciones ordenadas
    for (const auto& song : songs) {
        std::cout << song.getTrackName() << " - " << song.getArtistName();
        if (criteria == "popularidad") std::cout << " (Popularidad: " << song.getPopularity() << ")";
        else if (criteria == "año") std::cout << " (Año: " << song.getYear() << ")";
        else if (criteria == "duracion") std::cout << " (Duración: " << song.getDuration() << " ms)";
        else if (criteria == "genero") std::cout << " (Género: " << song.getGenre() << ")";
        std::cout << "\n";
    }
}
// Elimina una canción globalmente de todas las estructuras

void deleteSongGlobal(DoublyLinkedList& list, HashTable& hashTable, AVLTree& avlTree, const std::string& trackId) {
    int year = 0;

    // Eliminar canción de la lista y obtener su año
    if (list.removeSong(trackId, year)) {
        // Eliminar de la tabla hash
        hashTable.remove(year, trackId);
        // Eliminar del arbol AVL
        avlTree.remove(trackId);
        std::cout << "Canción eliminada de todas las estructuras.\n";
    } else {
        std::cout << "Canción no encontrada.\n";

    }
}

void displaySongsByYear(HashTable& hashTable, int year) {
    std::list<Song> songs = hashTable.find(year);

    if (songs.empty()) {
        std::cout << "No se encontraron canciones para el año " << year << ".\n";
        return;
    }

    std::cout << "Canciones del año " << year << ":\n";
    for (const auto& song : songs) {
        std::cout << song.getTrackName() << " - " << song.getArtistName()
                  << " (Popularidad: " << song.getPopularity()
                  << ", Duración: " << song.getDuration() << " ms)\n";
    }
}
