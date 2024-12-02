#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "DoublyLinkedList.h"
#include "HashTable.h"
#include "AVLTree.h"

int getValidatedOption(int min, int max);
void loadSongsFromCSV(const std::string& filename, DoublyLinkedList& list, HashTable& hashTable, AVLTree& avlTree);
void displaySorted(DoublyLinkedList& list, const std::string& criteria, bool ascending);
void deleteSongGlobal(DoublyLinkedList& list, HashTable& hashTable, AVLTree& avlTree, const std::string& trackId);
void displaySongsByYear(HashTable& hashTable, int year);


#endif // UTILS_H
