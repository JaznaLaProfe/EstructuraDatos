/**
 * @file tipos.h
 * @author Jazna Meza Hidalgo (ymeza@ubiobio.cl)
 * @brief Implementacion de tipos de datos para trabajar con números y cadenas
 * @version 0.1
 * @date 2025-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { TIPO_INT, TIPO_STRING } TipoDato;

typedef struct s_dato {
    TipoDato tipo;
    union {
        int entero;
        char cadena[500]; 
    } valor;
} DATO;

typedef struct s_nodo {
    DATO elemento;
    struct s_nodo *izquierdo, *derecho;
} *NODO;
