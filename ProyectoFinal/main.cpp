#include "DoublyLinkedList.h"
#include "HashTable.h"
#include "AVLTree.h"
#include <fstream>
#include <sstream>
#include <iostream>

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
}int main() {
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
            case 1: {
                std::string id, artist, track, genre;
                int year, popularity, duration;
                std::cout << "Ingrese ID: "; std::cin >> id;
                std::cout << "Ingrese Artista: "; std::cin.ignore(); std::getline(std::cin, artist);
                std::cout << "Ingrese Canción: "; std::getline(std::cin, track);
                std::cout << "Ingrese Género: "; std::getline(std::cin, genre);
                std::cout << "Ingrese Año: "; std::cin >> year;
                std::cout << "Ingrese Popularidad: "; std::cin >> popularity;
                std::cout << "Ingrese Duración: "; std::cin >> duration;

                Song newSong(id, artist, track, genre, year, popularity, duration);
                playlist.addSong(newSong);
                hashTable.insert(newSong);
                avlTree.insert(newSong);
                break;
            }
            case 2: {
                std::string id;
                std::cout << "Ingrese ID de la canción a eliminar: "; std::cin >> id;
                if (playlist.removeSong(id)) {
                    hashTable.remove(id);
                    std::cout << "Canción eliminada.\n";
                } else {
                    std::cout << "Canción no encontrada.\n";
                }
                break;
            }
            case 3: {
                std::string id;
                std::cout << "Ingrese ID de la canción a buscar: "; std::cin >> id;
                Song* song = hashTable.find(id);
                if (song) {
                    std::cout << "Canción encontrada: " << song->getTrackName() << " - " 
                              << song->getArtistName() << std::endl;
                } else {
                    std::cout << "Canción no encontrada.\n";
                }
                break;
            }
            case 4:
                std::cout << "Canciones en la lista:\n";
                playlist.printAll();
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
