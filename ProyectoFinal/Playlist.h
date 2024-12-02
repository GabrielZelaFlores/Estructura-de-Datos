#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "DoublyLinkedList.h"
#include "HashTable.h"
#include "AVLTree.h"

struct Playlist {
    std::string name;
    DoublyLinkedList list;
    HashTable hashTable;
    AVLTree avlTree;

    Playlist(const std::string& name) : name(name) {}
    Playlist(const std::string& name, const DoublyLinkedList& list, const HashTable& hashTable, const AVLTree& avlTree)
        : name(name), list(list), hashTable(hashTable), avlTree(avlTree) {}
};
#endif // PLAYLIST_H
