/* 
	@objetivo. Implementacion de tipos de datos para trabajar con ABB
	@autor. Jazna Meza Hidalgo
	@version. Mayo 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { TIPO_INT, TIPO_STRING } TipoDato;

typedef struct s_dato {
    TipoDato tipo;
    union {
        int entero;
        char cadena[50]; 
    } valor;
} DATO;

typedef struct s_nodo {
    DATO elemento;
    struct s_nodo *izquierdo, *derecho;
} *NODO;
