#include <stdio.h>
#include <stdlib.h>

/* Estructura */
typedef struct {
    int *elementos;
    int capacidad;
    int total;
} HEAP;

/* Operaciones */
void intercambio(int *a, int *b);
int padre(int i);
int hijoIzquierdo(int i);
int hijoDerecho(int i);
HEAP* createHeap(int capacidad);
int insertar(HEAP *heap, int valor);
void heapify(HEAP *heap, int i);
int extraerMinimo(HEAP *heap);
int esVacio(HEAP heap);
void verPorNiveles(HEAP *heap) ;

/**
 * @brief Intercambio de valores de dos variables
 * 
 * @param a direccion de memoria del primer valor a intercambiar
 * @param b direccion de memoria del segundo valor a intercambiar
 */
void intercambio(int *a, int *b) {
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
int padre(int i) {
    return (i - 1) / 2;
}

/**
 * @brief Otiene la ubicacion del hijo izquierdo de un elemento dado su indice
 * 
 * @param i indice del elemento del cual se desea saber la ubicacion de su hijo izquierdo 
 * @return indice del hijo izquierdo
 */
int hijoIzquierdo(int i) {
    return 2 * i + 1;
}

/**
 * @brief Otiene la ubicacion del hijo derecho de un elemento dado su indice
 * 
 * @param i indice del elemento del cual se desea saber la ubicacion de su hijo derecho 
 * @return indice del hijo derecho
 */
int hijoDerecho(int i) {
    return 2 * i + 2;
}

/**
 * @brief Crea un HEAP considerando la capacidad maxima entregada
 * 
 * @param capacidad cantidad maxima de elementos que tendra el HEAP
 * 
 * @return puntero al HEAP creado
 */
HEAP* createHeap(int capacidad) {
    HEAP *heap = (HEAP*) malloc(sizeof(HEAP));
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
int insertar(HEAP *heap, int valor) {
    if (heap->total == heap->capacidad) {
        return -1;
    }

    heap->total++;
    int i = heap->total - 1;
    heap->elementos[i] = valor;

    while (i != 0 && heap->elementos[padre(i)] > heap->elementos[i]) {
        intercambio(&heap->elementos[i], &heap->elementos[padre(i)]);
        i = padre(i);
    }
    return 1;
}

/**
 * @brief Reparar el heap, para mantener la propiedad del heap después de eliminar el elemento raíz
 * Mueve el elemento hacia abajo hasta que la propiedad del heap se mantenga. 
 * 
 * @param heap puntero al heapa reparar
 * @param i indice del elemento a mover
 * 
 */
void heapify(HEAP *heap, int i) {
    int menor = i;
    int izquierdo = hijoIzquierdo(i);
    int derecho = hijoDerecho(i);

    if (izquierdo < heap->total && heap->elementos[izquierdo] < heap->elementos[menor]) {
        menor = izquierdo;
    }

    if (derecho < heap->total && heap->elementos[derecho] < heap->elementos[menor]) {
        menor = derecho;
    }

    if (menor != i) {
        /* Intercambia */
        intercambio(&heap->elementos[i], &heap->elementos[menor]);
        /* Repara */
        heapify(heap, menor);
    }
}

/**
 * @brief Extrae y retorna la cabeza del HEAP
 * 
 * @param heap puntero al heapa reparar
 * 
 * @return valor en la cabeza del HEAP que ha sido extraido
 */
int extraerMinimo(HEAP *heap) {
    if (esVacio(*heap)) {
        return -1;
    }

    if (heap->total == 1) {
        heap->total--;
        return heap->elementos[0];
    }

    int raiz = heap->elementos[0];
    heap->elementos[0] = heap->elementos[heap->total - 1];
    heap->total--;
    heapify(heap, 0);

    return raiz;
}

/**
 * @brief Determina si el HEAP es vacio
 * 
 * @param heap heap a revisar
 * 
 * @return 1 en caso de que sea vacio y 0 en caso contrario
 */
int esVacio(HEAP heap){
    return heap.total == 0;
}

/**
 * @brief Imprime el heap por niveles, considerando el nivel 0 como el nivel de la raiz
 * 
 * @param heap direccion de memoria del heap a visualizar
 */
void verPorNiveles(HEAP *heap) {

    printf("** HEAP por niveles **\n");
    if (esVacio(*heap)) {
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




