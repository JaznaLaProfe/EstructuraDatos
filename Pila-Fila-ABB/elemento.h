/**
 * @file elemento.h
 * @author Jazna Meza Hidalgo (ymeza@ubiobio.cl)
 * @brief Implementacion de tipo de dato genérico
 * @version 0.1
 * @date 2025-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "tipos.h"
 
/* Definicion de tipo de datos */
typedef struct s_elemento{
    DATO valor;
    struct s_elemento *siguiente;
}*ELEMENTO;

/**
 * @brief crea un nuevo elemento con el valor indicado
 * @param valor elemento que sera creado
 * @return direccion de memoria del elemento creado
 */
ELEMENTO crearElementoEntero(int valor){
    ELEMENTO e = (ELEMENTO) malloc(sizeof(struct s_elemento));
    e->valor.tipo = TIPO_INT;
    e->valor.valor.entero = valor;
    e->siguiente = NULL;
    return e;
}

ELEMENTO crearElementoCadena(char *valor){
    ELEMENTO e = (ELEMENTO) malloc(sizeof(struct s_elemento));
    e->valor.tipo = TIPO_STRING;
    strcpy(e->valor.valor.cadena, valor);
    e->siguiente = NULL;
    return e;

}

/** 
 * @brief muestra en pantalla los datos del elemento
 * @param e elemento a ser visualizado
 */
void verElemento(ELEMENTO e){
    if (e->valor.tipo == TIPO_INT) printf("{%d}->", e->valor.valor.entero);
    else printf("{%s}->", e->valor.valor.cadena);

}