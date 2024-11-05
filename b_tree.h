#ifndef B_TREE_H
#define B_TREE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 5      // Máximo número de claves por nodo
#define DECIMALES 10000000

// Estructura del nodo en el B-tree
struct BTreeNode {
    int num_keys;
    int keys[MAX_KEYS];
    struct BTreeNode *children[MAX_KEYS + 1];
};

// Prototipos de funciones para manipulación del B-tree
struct BTreeNode *createNode();
void insert(struct BTreeNode **root, int key);
void splitChild(struct BTreeNode *parent, int index);
void insertNonFull(struct BTreeNode *node, int key);
void insertKey(struct BTreeNode *node, int key);
void printInOrder(struct BTreeNode *node);
void generateDotFile(struct BTreeNode *root, const char *filename);
void writeNode(FILE *file, struct BTreeNode *node, int *nodeCount);
void importCSVAndCreateBTree(const char *filename, struct BTreeNode **root);
int search(struct BTreeNode *node, int key);

#endif // B_TREE_H
