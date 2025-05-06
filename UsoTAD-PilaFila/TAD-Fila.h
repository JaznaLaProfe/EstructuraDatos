/**
 * @file TAD-Fila.h
 * @author Jazna Meza Hidalgo (ymeza@ubiobio.cl)
 * @brief implementar al TAD fila
 * @version 0.1
 * @date 2025-04-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_fila{
    ELEMENTO primero, ultimo;
} FILA;

/**
 * @brief Crea la fila
 * 
 * @return FILA nueva fila
 */
FILA crearFila(){
    FILA nueva;
    nueva.primero = nueva.ultimo = NULL;
    return nueva;
}

/**
 * @brief Retorna un indicador para saber si la fila esta vacia
 * Una fila es vacia si el primer elemento es NULL
 * @param f fila a procesar 
 * @return int 1 en caso de que la fila este vacia y 0 en caso contrario
 */
int empty(FILA f){
    return f.primero == NULL;
} 

/**
 * @brief Inserta un elemento en la fila, siguiendo la regla FIFO
 * 
 * @param f puntero a la fila que sera modificada
 * @param nuevo direccion de memoria del elemento a ser agregaado
 */
void insert(FILA *f, ELEMENTO nuevo){
    if (!empty(*f)){
        (*f).ultimo->siguiente = nuevo;
        (*f).ultimo = nuevo;
    }
    else{
        (*f).primero = (*f).ultimo = nuevo;
    }    
}

/**
 * @brief Extrae un elemento de la fila respetando el criterio FIFO
 * 
 * @param f direccion de memoria de la fila a procesar
 */
void extract(FILA *f){
    if (!empty(*f)){
        (*f).primero = (*f).primero->siguiente;
    }    
}

/**
 * @brief Retornar el primer elemento de la fila
 * 
 * @param f fila a ser procesada
 * @return ELEMENTO direccion de memoria del primer elemento de la fila
 */
ELEMENTO verPrimero(FILA f){
    return f.primero;
}

/**
 * @brief Retorna el ultimo elemento de la fila
 * 
 * @param f fila a ser procesada
 * @return ELEMENTO direccion de memoria del ultimo elemento de la fila
 */
ELEMENTO verUltimo(FILA f){
    return f.ultimo;
}

/**
 * @brief Imprime el primer y ultimo elemento de la fila
 * 
 * @param f fila a procesar
 */
void infoFila(FILA f){
    printf("Primero -> %d - Ultimo-> %d\n", f.primero->numero, f.ultimo->numero);
}

/**
 * @brief Muestra en pantalla el contenido de la fila
 * 
 * @param f fila a procesar
 */
void verFila(FILA f) {
    while (!empty(f)) {
        verElemento(verPrimero(f));
        extract(&f);
    }
}

