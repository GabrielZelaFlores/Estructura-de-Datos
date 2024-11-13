#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b_tree.h"

// Crea un nuevo nodo del B-tree
struct BTreeNode *createNode() {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL) {
        printf("La asignación de memoria falló.\n");
        exit(1);
    }
    newNode->num_keys = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Inserta una clave en el B-tree
void insert(struct BTreeNode **root, int key) {
    if (*root == NULL) {
        *root = createNode();
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    } else {
        if ((*root)->num_keys == MAX_KEYS) {
            struct BTreeNode *newRoot = createNode();
            newRoot->children[0] = *root;
            splitChild(newRoot, 0);
            *root = newRoot;
            int i = (key > newRoot->keys[0]) ? 1 : 0;
            insertNonFull(newRoot->children[i], key);
        } else {
            insertNonFull(*root, key);
        }
    }
}

// Divide un nodo lleno y ajusta la estructura del B-tree
void splitChild(struct BTreeNode *parent, int index) {
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newChild = createNode();
    int medianIndex = MAX_KEYS / 2;

    newChild->num_keys = MAX_KEYS - medianIndex - 1;
    for (int i = 0; i < newChild->num_keys; i++) {
        newChild->keys[i] = child->keys[i + medianIndex + 1];
    }

    if (child->children[0] != NULL) {
        for (int i = 0; i <= newChild->num_keys; i++) {
            newChild->children[i] = child->children[i + medianIndex + 1];
        }
    }

    child->num_keys = medianIndex;
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;

    for (int i = parent->num_keys; i > index; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }
    parent->keys[index] = child->keys[medianIndex];
    parent->num_keys++;
}

// Inserta una clave en un nodo que no está lleno
void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->num_keys - 1;
    if (node->children[0] == NULL) {
        insertKey(node, key);
        return;
    }

    while (i >= 0 && node->keys[i] > key) {
        i--;
    }
    i++;
    if (node->children[i]->num_keys == MAX_KEYS) {
        splitChild(node, i);
        if (node->keys[i] < key) {
            i++;
        }
    }
    insertNonFull(node->children[i], key);
}

// Inserta una clave directamente en un nodo
void insertKey(struct BTreeNode *node, int key) {
    int i = node->num_keys - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    node->keys[i + 1] = key;
    node->num_keys++;
}

// Imprime las claves en orden ascendente
void printInOrder(struct BTreeNode *node) {
    if (node == NULL) return;

    for (int i = 0; i < node->num_keys; i++) {
        printInOrder(node->children[i]);
        printf("%d ", node->keys[i]);
    }
    printInOrder(node->children[node->num_keys]);
}

// Genera un archivo DOT para visualizar el B-tree
void generateDotFile(struct BTreeNode *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    fprintf(file, "digraph BTree {\n");
    fprintf(file, "    node [shape=record];\n");

    int nodeCount = 0;
    writeNode(file, root, &nodeCount);

    fprintf(file, "}\n");
    fclose(file);
    printf("Archivo DOT generado correctamente en %s\n", filename);
}

// Escribe recursivamente los nodos y sus conexiones en el archivo DOT
void writeNode(FILE *file, struct BTreeNode *node, int *nodeCount) {
    if (node == NULL) return;

    int currentNode = (*nodeCount)++;
    fprintf(file, "    node%d [label=\"", currentNode);

    int lastPortIndex = 0;
    for (int i = 0; i < node->num_keys; i++) {
        if (i > 0) fprintf(file, " | ");
        lastPortIndex = i * 2;
        fprintf(file, "<f%d>%d", lastPortIndex, node->keys[i]);
        if (i < node->num_keys - 1) fprintf(file, " | <f%d>", lastPortIndex + 1);
    }

    fprintf(file, " | <f%d>", lastPortIndex + 1);
    fprintf(file, "\"];\n");

    int childPortIndex = 0;
    for (int i = 0; i <= node->num_keys; i++) {
        if (node->children[i] != NULL) {
            int childNode = *nodeCount;
            writeNode(file, node->children[i], nodeCount);

            childPortIndex = (i == 0) ? 0 : (i == 1) ? 1 : (i * 2) - 1;
            fprintf(file, "    node%d:f%d -> node%d:f0;\n", currentNode, childPortIndex, childNode);
        }
    }
}

// Importa claves de un archivo CSV y las inserta en el B-tree
void importCSVAndCreateBTree(const char *filename, struct BTreeNode **root) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        token = strtok(NULL, ",");
        if (token != NULL) {
            double value = atof(token);
            int key = (int)(value * DECIMALES);
            if (!search(*root, key)) {
                insert(root, key);
            }
        }
    }

    fclose(file);
    printf("Datos importados y B-tree creado correctamente.\n");
}

// Busca una clave en el B-tree
int search(struct BTreeNode *node, int key) {
    while (node != NULL) {
        int i = 0;
        while (i < node->num_keys && key > node->keys[i]) {
            i++;
        }
        if (i < node->num_keys && key == node->keys[i]) {
            return 1;
        }
        node = node->children[i];
    }
    return 0;
}
