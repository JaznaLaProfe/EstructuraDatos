#include <stdio.h>
#include <stdlib.h>

#include "TAD-Grafo.h"
#include "min-heap.h"
#include "max-heap.h"

/* Prototipo de funciones */
HEAP *etapa_uno(MATRIZ_ADYACENCIA);
MAX_HEAP *etapa_dos(HEAP *, int);

int main(int argc, char *argv[]){
    MATRIZ_ADYACENCIA gx = crearMatrizGrafo(argv[1], argv[2], atoi(argv[3]));
    verMatrizGrafo(gx);
    /* Ejecutar etapa 1 */
    HEAP *r_uno = etapa_uno(gx);
    /* Ver heap de mínimos generado */
    verPorNiveles(r_uno);
    /* Ejecutar etapa 2 */
    int k = atoi(argv[4]);
    MAX_HEAP *r_dos = etapa_dos(r_uno, k);
    printf("Los %d más influyentes son:\n", k);
    verPorNivelesMaxHeap(r_dos);
    return 0;
}

HEAP *etapa_uno(MATRIZ_ADYACENCIA g){
    /* Crear el HEAP de mínimos */
    HEAP *h = createHeap(g.total_vertices);
    /* Procesa cada vértice */
    for(int i=0; i < g.total_vertices; i++){
        int contador = 0;
        int visitado[MAX_VERTICES] = {0};

        for(int j=0; j < g.total_vertices; j++){
            /* Verificar si se trata de un vecino directo */
            if (g.matriz[i][j] > 0){
                for(int k=0; k < g.total_vertices; k++){
                    /* Verifica que se trata de un vecino directo y que no se haya visitado */
                    if (g.matriz[j][k] > 0 && k != i && !visitado[k]){
                        visitado[k] = 1;
                        contador+=1;                        
                    }
                }
            }
        }
        printf("Influencia de %c = %d\n", g.nombre_vertices[i], contador);
        /* Insertar en el HEAP en base al requerimiento */
        insertar(h, contador);
    }
    return h;
}

MAX_HEAP *etapa_dos(HEAP *h, int k){
    MAX_HEAP *hm = createMaxHeap(h->capacidad);

    /* Traspasa del heap de mínimos al heap de máximos */
    while(!esVacio(*h)){
        int valor = extraerMinimo(h);
        insertarMaxHeap(hm, valor);
    }
    MAX_HEAP *resultado = createMaxHeap(k);
    int contador = 0;
    while(!esVacioMaxHeap(*hm) && contador < k){
        int valor = extraerMaximo(hm);
        insertarMaxHeap(resultado, valor);
        contador+=1;
    }
    return resultado;
}