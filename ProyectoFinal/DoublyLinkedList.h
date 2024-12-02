#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Song.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

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

    Node* getHead() const { return head; }

    void addSong(const Song& song) {
        Node* newNode = new Node(song);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    
    bool removeSong(const std::string& trackId, int& year) {
        Node* current = head;
        while (current) {
            if (current->song.getTrackId() == trackId) {
                year = current->song.getYear(); // Extraer el año antes de eliminar
            
                // Lógica existente para eliminar el nodo
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;

                delete current; // Liberar memoria del nodo
                return true;    // Indicar que se eliminó
            }
            current = current->next;
        }
        return false; // No se encontró la canción
    }



    void changeOrder(int currentPos, int newPos) {
        if (currentPos == newPos || !head) return;

        Node* current = head;
        int index = 0;

        // Encontrar la posición actual
        while (current && index < currentPos) {
            current = current->next;
            index++;
        }
        if (!current) return; // Posición actual inválida

        // Desvincular nodo actual
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;

        // Insertar en la nueva posición
        Node* newCurrent = head;
        index = 0;
        while (newCurrent && index < newPos) {
            newCurrent = newCurrent->next;
            index++;
        }
        if (!newCurrent) { // Insertar al final
            tail->next = current;
            current->prev = tail;
            tail = current;
            current->next = nullptr;
        } else { // Insertar antes de newCurrent
            current->next = newCurrent;
            current->prev = newCurrent->prev;
            if (newCurrent->prev) newCurrent->prev->next = current;
            newCurrent->prev = current;
            if (newCurrent == head) head = current;
        }
    }

    void shuffle() {
        std::vector<Node*> nodes;
        Node* current = head;

        // Agregar todos los nodos al vector
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }

        // Barajar los nodos
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(nodes.begin(), nodes.end(), g);

        // Reconstruir la lista
        head = nodes[0];
        Node* prev = nullptr;
        for (auto node : nodes) {
            node->prev = prev;
            if (prev) prev->next = node;
            prev = node;
        }
        tail = prev;
        tail->next = nullptr;
    }

    std::vector<Song> toVector() const {
        std::vector<Song> songs;
        Node* current = head;
        while (current) {
            songs.push_back(current->song);
            current = current->next;
        }
        return songs;
    }

    void printAll() const {
        Node* current = head;
        while (current) {
            std::cout << current->song.getTrackName() << " - " 
                      << current->song.getArtistName() << " ( Genero: " 
                      << current->song.getGenre() << " , Año: " 
                      << current->song.getYear() << " )" << std::endl;
            current = current->next;
        }
    } 
  
void printReverse() const {
    Node* current = tail; // Comenzar desde el último nodo
    while (current) { // Mientras existan nodos
        std::cout << current->song.getTrackName() << " - " 
                  << current->song.getArtistName() << " ( Genero: " 
                  << current->song.getGenre() << " , Año: " 
                  << current->song.getYear() << " )" << std::endl;
        current = current->prev; // Moverse al nodo anterior
    }
}

};

#endif

