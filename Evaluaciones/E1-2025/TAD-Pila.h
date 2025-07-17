/**
 * @file TAD-Pila.h
 * @author Jazna Meza Hidalgo (ymeza@ubiobio.cl)
 * @brief implementar al TAD pila
 * @version 0.1
 * @date 2025-04-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_pila{
    ELEMENTO tope;
} PILA;

/**
 * @brief crea una pila vacia
 * @return pila vacia
 */
PILA crearPila(){
    PILA nueva;
    nueva.tope = NULL;
    return nueva;
}

/**
 * @brief agrega un elemento en el tope de la pila
 * @param p direccion de memoria de la pila
 * @param nuevo elemento que será agregado al tope de la pila
 */
void push(PILA *p, ELEMENTO nuevo){
    nuevo->siguiente = (*p).tope;
    (*p).tope = nuevo;    
}

/**
 * @brief determina si una pila esta vacia
 * @param p direccion de memoria de la pila
 * @return 1 en caso de que la pila este vacia y 0 en caso contrario
 */
int isEmpty(PILA p){
    return p.tope == NULL;
} 

/**
 * @brief extrae el tope de la pila
 * @param p pila que sera modificada (se le extrae su tope)
 * @return direccion de memoria de la pila modificada
 */
void pop(PILA *p){    
    if ((*p).tope != NULL){        
        (*p).tope = (*p).tope->siguiente;
    }    
}

/**
 * @brief retorna el tope de la pila
 * @param p pila de la cual se quiere saber su tope
 * @return elemento que se encuentra en el tope
 */
ELEMENTO verTope(PILA p){
    return p.tope;
}



/**
 * @brief clona una pila
 * @param p pila que sera clonada
 * @return pila clonada
 */
PILA clonar(PILA p){
    PILA clonada = crearPila();
    while(!isEmpty(p)){
        push(&clonada, crearElemento(verTope(p)->numero));
        pop(&p);
    }
    return clonada;
}

/**
 * @brief Muestra en pantalla el contenido de la pila
 * 
 * @param p pila a ser procesada
 */
void verPila(PILA p) {
    while (!isEmpty(p)) {
        verElemento(verTope(p));
        pop(&p);
    }
}

