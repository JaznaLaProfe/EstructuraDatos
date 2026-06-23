#include <stdio.h>
#include <stdlib.h>

#include "TAD-Grafo.h"
#include "min-heap.h"
#include "max-heap.h"

int main(int argc, char *argv[]){
    MATRIZ_ADYACENCIA gx = crearMatrizGrafo(argv[1], argv[2], atoi(argv[3]));
    verMatrizGrafo(gx);
    return 0;
}