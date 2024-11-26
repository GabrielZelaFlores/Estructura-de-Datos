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

    bool removeSong(const std::string& trackId) {
        Node* current = head;
        while (current) {
            if (current->song.getTrackId() == trackId) {
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;
                delete current;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void printAll() const {
        Node* current = head;
        while (current) {
            std::cout << current->song.getTrackName() << " - " 
                      << current->song.getArtistName() << std::endl;
            current = current->next;
        }
    }
};

#endif
