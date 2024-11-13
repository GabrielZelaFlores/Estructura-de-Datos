#include <stdio.h>
#include <time.h>
#include "b_tree.h"

// INTEGRANTES:
// Huamani Vásquez Juan José
// Valdivia Vásquez Gian Pool
// Zela Flores Gabriel Frank

int main() {
    struct BTreeNode *root = NULL;
    struct timespec inicio, fin;
    long tiempo_transcurrido;

    const char *filename = "data/random_numbers_1000000.csv"; // Ruta del archivo CSV
    importCSVAndCreateBTree(filename, &root);
    
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    int searched = search(root, 6677025);  // Buscar clave específica en el árbol
    clock_gettime(CLOCK_MONOTONIC, &fin);

    tiempo_transcurrido = (fin.tv_sec - inicio.tv_sec) * 1000000000L + (fin.tv_nsec - inicio.tv_nsec);
    
    printf("Número encontrado (0/1): %d\n", searched);
    printf("Tiempo de búsqueda: %ld nanosegundos\n", tiempo_transcurrido);
    
    return 0;
}
