#include <stdio.h>
#include <stdlib.h>

/* Estructura */
typedef struct {
    int *elementos;
    int capacidad;
    int total;
} MAX_HEAP;

/* Operaciones */
void intercambioMaxHeap(int *a, int *b);
int padreMaxHeap(int i);
int hijoIzquierdoMaxHeap(int i);
int hijoDerechoMaxHeap(int i);
MAX_HEAP* createMaxHeap(int capacidad);
int insertarMaxHeap(MAX_HEAP *heap, int valor);
void heapifyMaxHeap(MAX_HEAP *heap, int i);
int extraerMaximo(MAX_HEAP *heap);
int esVacioMaxHeap(MAX_HEAP heap);
void verPorNivelesMaxHeap(MAX_HEAP *heap) ;

/**
 * @brief Intercambio de valores de dos variables
 * 
 * @param a direccion de memoria del primer valor a intercambiar
 * @param b direccion de memoria del segundo valor a intercambiar
 */
void intercambioMaxHeap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Obtiene la ubicacion del padre de un elemento dado su indice
 * 
 * @param i indice del elemento del cual se desea saber la ubicacion de su padre
 * @return indice del padre
 */
int padreMaxHeap(int i) {
    return (i - 1) / 2;
}

/**
 * @brief Otiene la ubicacion del hijo izquierdo de un elemento dado su indice
 * 
 * @param i indice del elemento del cual se desea saber la ubicacion de su hijo izquierdo 
 * @return indice del hijo izquierdo
 */
int hijoIzquierdoMaxHeap(int i) {
    return 2 * i + 1;
}

/**
 * @brief Otiene la ubicacion del hijo derecho de un elemento dado su indice
 * 
 * @param i indice del elemento del cual se desea saber la ubicacion de su hijo derecho 
 * @return indice del hijo derecho
 */
int hijoDerechoMaxHeap(int i) {
    return 2 * i + 2;
}

/**
 * @brief Crea un HEAP considerando la capacidad maxima entregada
 * 
 * @param capacidad cantidad maxima de elementos que tendra el HEAP
 * 
 * @return puntero al HEAP creado
 */
MAX_HEAP* createMaxHeap(int capacidad) {
    MAX_HEAP *heap = (MAX_HEAP*) malloc(sizeof(MAX_HEAP));
    heap->elementos = (int*) malloc(capacidad * sizeof(int));
    heap->capacidad = capacidad;
    heap->total = 0;
    return heap;
}
/**
 * @brief Inserta un nuevo elemento en el HEAP
 * 
 * @param heap puntero al HEAP al cual se pretende agregar el elemento
 * @param valor elemento a ser agregado
 * 
 * @return -1 en caso de que el HEAP no tenga capacidad y 1 en caso contrario
 */
int insertarMaxHeap(MAX_HEAP *heap, int valor) {
    if (heap->total == heap->capacidad) {
        return -1;
    }

    heap->total++;
    int i = heap->total - 1;
    heap->elementos[i] = valor;

    while (i != 0 && heap->elementos[padreMaxHeap(i)] < heap->elementos[i]) {
        intercambioMaxHeap(&heap->elementos[i], &heap->elementos[padreMaxHeap(i)]);
        i = padreMaxHeap(i);
    }
    return 1;
}

/**
 * @brief Reparar el heap, para mantener la propiedad del heap después de eliminar el elemento raíz
 * Mueve el elemento hacia arriba hasta que la propiedad del heap se mantenga. 
 * 
 * @param heap puntero al heapa reparar
 * @param i indice del elemento a mover
 * 
 */
void heapifyMaxHeap(MAX_HEAP *heap, int i) {
    int mayor = i;
    int izquierdo = hijoIzquierdoMaxHeap(i);
    int derecho = hijoDerechoMaxHeap(i);

    if (izquierdo < heap->total && heap->elementos[izquierdo] > heap->elementos[mayor]) {
        mayor = izquierdo;
    }

    if (derecho < heap->total && heap->elementos[derecho] > heap->elementos[mayor]) {
        mayor = derecho;
    }

    if (mayor != i) {
        /* Intercambia */
        intercambioMaxHeap(&heap->elementos[i], &heap->elementos[mayor]);
        /* Repara */
        heapifyMaxHeap(heap, mayor);
    }
}

/**
 * @brief Extrae y retorna la cabeza del HEAP
 * 
 * @param heap puntero al heap a reparar
 * 
 * @return valor en la cabeza del HEAP que ha sido extraido
 */
int extraerMaximo(MAX_HEAP *heap) {
    if (esVacioMaxHeap(*heap)) {
        return -1;
    }

    if (heap->total == 1) {
        heap->total--;
        return heap->elementos[0];
    }

    int raiz = heap->elementos[0];
    heap->elementos[0] = heap->elementos[heap->total - 1];
    heap->total--;
    heapifyMaxHeap(heap, 0);

    return raiz;
}

/**
 * @brief Determina si el HEAP es vacio
 * 
 * @param heap heap a revisar
 * 
 * @return 1 en caso de que sea vacio y 0 en caso contrario
 */
int esVacioMaxHeap(MAX_HEAP heap){
    return heap.total == 0;
}

/**
 * @brief Imprime el heap por niveles, considerando el nivel 0 como el nivel de la raiz
 * 
 * @param heap direccion de memoria del heap a visualizar
 */
void verPorNivelesMaxHeap(MAX_HEAP *heap) {

    printf("** HEAP por niveles **\n");
    if (esVacioMaxHeap(*heap)) {
        printf("\nHeap vacio\n");
        return;
    }

    int nivel = 0;
    int nodosNivelActual = 1;
    int i = 0;

    while (i < heap->total) {
        printf("\tNivel %d: ", nivel);
        int nodosImpresos = 0;

        while (nodosImpresos < nodosNivelActual && i < heap->total) {
            printf("%d ", heap->elementos[i]);
            i+=1;
            nodosImpresos+=1;
        }

        printf("\n");
        nivel+=1;
        nodosNivelActual *= 2; // Duplicar el número de nodos esperados en el siguiente nivel
    }
}




