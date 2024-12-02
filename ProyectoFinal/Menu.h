#ifndef MENU_H
#define MENU_H

#include "Playlist.h"
#include "Utils.h"

void menu(Playlist& playlist, const DoublyLinkedList& mainList);

// Menu.h
void menuImGui(DoublyLinkedList& list, HashTable& hashTable, AVLTree& avlTree, const DoublyLinkedList& mainList);

#endif // MENU_H
