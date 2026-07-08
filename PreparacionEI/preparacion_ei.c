/**
 * @file preparacion_ei.c
 * @author Jazna Meza Hidalgo
 * @brief Preparación evaluación de integración
 * @version 0.1
 * @date 2026-07-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "elemento.h"

#include "TAD-arbol.h"

#include "TAD-hash.h"
#include "min-heap.h"

HASH cargarDatos(NODO numeros, int c);
NODO crearArbol(char *archivo);
HEAP* procesar(HASH tabla);

/* Función principal */
int main(int argc, char *argv[]){
    NODO mis_numeros;
    HASH mi_tabla;
    /* Valida la cantidad de parámetros */
    if (argc != 3){
        printf("Uso correcto: %s archivo.txt capacidad\n", argv[0]);
        return 0;
    }
    mis_numeros = crearArbol(argv[1]);
    printf("Datos cargados en el árbol\n");
    mi_tabla = cargarDatos(mis_numeros, atoi(argv[2]));
    printf("Datos cargados en la tabla\n");
    verTablaHash(mi_tabla, "Tabla-EI.txt");
    HEAP *r = procesar(mi_tabla);
    verPorNiveles(r);
    return 1;
}

DATO obtieneMenor(NODO r){
    NODO aux = r;
    while (aux->izquierdo != NULL){
        aux = aux->izquierdo;
    }
    return aux->elemento;
}
/**
 * @brief crea una tabla HASH de capacidad c y carga los datos desde el archivo 
 * indicado
 * El archivo sólo contiene valores numéricos (una línea contiene un número)
 * @param archivo nombre del archivo
 * @param c capacidad de la tabla
 * @return HASH tabla hash conteniendo los valores del archivo
 */
HASH cargarDatos(NODO numeros, int c){
    HASH nueva = crearTabla(c);
    int numero;
    NODO seleccionados = numeros;
    while (seleccionados != NULL){
        numero = obtieneMenor(seleccionados).valor.entero;
        nueva = agregarClave(nueva, numero);
        seleccionados = remover(seleccionados, crearDatoEntero(numero));
    }
    return nueva;
}

/**
 * @brief Retorna una estructura donde se puedan realizar búsquedas rápidas
 * 
 * @param archivo 
 * @return NODO 
 */
NODO crearArbol(char *archivo){
    NODO mis_valores = NULL;
    FILE *fp = fopen(archivo, "r");
    int numero;
    while(!feof(fp)){   
        fscanf(fp, "%d\n", &numero);  
        mis_valores = agregarNodo(mis_valores, crearDatoEntero(numero));        
    }
    return mis_valores;
}


HEAP* procesar(HASH tabla){
    int total;
    ELEMENTO_H aux;
    HEAP *heap = createHeap(tabla.capacidad);
    
    for(int i = 0; i < tabla.capacidad; i++){
        /* Si la entrada está libre NO se procesa */
        if (tabla.libre[i]){            
            continue;
        }
        
        total = 1; //(tabla.libre[i]?0:1);
        /* Procesa los valores que han colisionado */
        aux = tabla.claves[i].entradas;
        while (aux != NULL){
            total += 1;
            aux = aux->siguiente;
        }
        insertar(heap, total);
    }
    return heap;
}