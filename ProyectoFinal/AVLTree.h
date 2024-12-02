#ifndef AVLTREE_H
#define AVLTREE_H

#include "Song.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* balance(Node* node) {
        int bf = balanceFactor(node);

        if (bf > 1 && balanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (bf < -1 && balanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, const Song& song) {
        if (!node) return new Node(song);

        if (song.getTrackId() < node->song.getTrackId()) {
            node->left = insert(node->left, song);
        } else if (song.getTrackId() > node->song.getTrackId()) {
            node->right = insert(node->right, song);
        } else {
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        return balance(node);
    }

    void searchByName(Node* node, const std::string& keyword, std::vector<Song>& results) {
        if (!node) return;

        std::string trackNameLower = node->song.getTrackName();
        std::string keywordLower = keyword;
        std::transform(trackNameLower.begin(), trackNameLower.end(), trackNameLower.begin(), ::tolower);
        std::transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

        if (trackNameLower.find(keywordLower) != std::string::npos) {
            results.push_back(node->song);
        }

        searchByName(node->left, keyword, results);
        searchByName(node->right, keyword, results);
    }
    void searchByAuthor(Node* node, const std::string& author, std::vector<Song>& results) const {
    if (!node) return;

    std::string nodeAuthor = node->song.getArtistName();
    std::string searchAuthor = author;
    std::transform(nodeAuthor.begin(), nodeAuthor.end(), nodeAuthor.begin(), ::tolower);
    std::transform(searchAuthor.begin(), searchAuthor.end(), searchAuthor.begin(), ::tolower);

    if (nodeAuthor.find(searchAuthor) != std::string::npos) {
        results.push_back(node->song);
    }

    searchByAuthor(node->left, author, results);
    searchByAuthor(node->right, author, results);
}

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* remove(Node* node, const std::string& trackId) {
        if (!node) return nullptr;

        if (trackId < node->song.getTrackId()) {
            node->left = remove(node->left, trackId);
        } else if (trackId > node->song.getTrackId()) {
            node->right = remove(node->right, trackId);
        } else {
            // Nodo encontrado, proceder a eliminar
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                // Nodo con dos hijos: obtener el sucesor en orden
                Node* temp = minValueNode(node->right);
                node->song = temp->song;
                node->right = remove(node->right, temp->song.getTrackId());
            }
        }

        // Actualizar la altura y balancear
        node->height = 1 + std::max(height(node->left), height(node->right));
        return balance(node);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }
void searchByGenre(Node* node, const std::string& genre, std::vector<Song>& results) const {
    if (!node) return;

    // Recorrido in-order para explorar todos los nodos
    searchByGenre(node->left, genre, results);
    if (node->song.getGenre() == genre) {
        results.push_back(node->song);
    }
    searchByGenre(node->right, genre, results);
}
void collectAllSongs(Node* node, std::vector<Song>& results) const {
    if (!node) return;
    collectAllSongs(node->left, results);
    results.push_back(node->song);
    collectAllSongs(node->right, results);
}
public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(const Song& song) {
        root = insert(root, song);
    }

    std::vector<Song> searchByName(const std::string& keyword) {
        std::vector<Song> results;
        searchByName(root, keyword, results);
        return results;
    }

    void displaySearchResults(const std::string& keyword) {
        auto results = searchByName(keyword);
        if (results.empty()) {
            std::cout << "No se encontraron canciones con la palabra clave: " << keyword << std::endl;
        } else {
            std::cout << "Canciones encontradas para \"" << keyword << "\":" << std::endl;
            for (const auto& song : results) {
                std::cout << " - " << song.getTrackName() << " de " << song.getArtistName() << " id: " << song.getTrackId() << std::endl;
            }
        }
    }
    
void searchByAuthor(const std::string& author) const {
    std::vector<Song> results;
    searchByAuthor(root, author, results);

    if (results.empty()) {
        std::cout << "No se encontraron canciones del autor \"" << author << "\".\n";
        return;
    }

    std::cout << "Canciones del autor \"" << author << "\":\n";
    for (const auto& song : results) {
        std::cout << song.getTrackName() << " - " << song.getArtistName()
                  << " (ID: " << song.getTrackId() << ", Popularidad: " << song.getPopularity()
                  << ", Duración: " << song.getDuration() << " ms)\n";
    }
}

    void remove(const std::string& trackId) {
        root = remove(root, trackId);
    }
void searchByGenre(const std::string& genre) const {
    std::vector<Song> results;
    searchByGenre(root, genre, results);

    if (results.empty()) {
        std::cout << "No se encontraron canciones del género \"" << genre << "\".\n";
        return;
    }

    // Mostrar opciones de ordenamiento
    std::cout << "Seleccione el criterio para ordenar las canciones:\n";
    std::cout << "1. Sin ordenar\n2. Por popularidad\n3. Por duración\n4. Alfabético (por nombre de canción)\n";
    int option;
    std::cin >> option;

    // Ordenar según el criterio seleccionado
    if (option == 2) {
        std::sort(results.begin(), results.end(), [](const Song& a, const Song& b) {
            return a.getPopularity() > b.getPopularity(); // Mayor a menor popularidad
        });
    } else if (option == 3) {
        std::sort(results.begin(), results.end(), [](const Song& a, const Song& b) {
            return a.getDuration() < b.getDuration(); // Menor a mayor duración
        });
    } else if (option == 4) {
        std::sort(results.begin(), results.end(), [](const Song& a, const Song& b) {
            return a.getTrackName() < b.getTrackName(); // Orden alfabético por título
        });
    }

    // Mostrar las canciones encontradas
    std::cout << "Canciones del género \"" << genre << "\":\n";
    for (const auto& song : results) {
        std::cout << song.getTrackName() << " - " << song.getArtistName()
                  << " (Popularidad: " << song.getPopularity()
                  << ", Duración: " << song.getDuration() << " ms)\n";
    }
}
void collectAllSongs(std::vector<Song>& results) const {
    collectAllSongs(root, results);
}
};

#endif


