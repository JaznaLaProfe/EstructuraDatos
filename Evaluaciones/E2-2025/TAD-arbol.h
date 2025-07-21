/* 
	@objetivo. Implementacion de arbol binario de busqueda (ABB)
	@autor. Jazna Meza Hidalgo
	@version. Mayo 2025
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "tipos.h"

/* Operaciones del árbol */
NODO agregarNodo(NODO, DATO);
/* Version recursivas de insercion de elementos en el ABB */
void insertar(NODO *, DATO);
NODO remover(NODO, DATO);
int buscar(NODO, DATO);
DATO verRaiz(NODO);

/* Operaciones dependiendo del tipo almacenado en el arbol */
NODO eliminarEntero(NODO, int);
NODO eliminarCadena(NODO, char*);
void insertarEntero(NODO *a, int elem);
void insertarCadena(NODO *a, char* elem);

DATO crearDatoEntero(int x);
DATO crearDatoCadena(char *texto);

/* Recorridos por profundidad */
void inOrden(NODO);
void preOrden(NODO);
void postOrden(NODO);

/* Implementacion de funciones */

/**
 * @brief Crea un elemento del tipo DATO conteniendo una cadena de texto para poder guardarlo luego en el arbol
 * 
 * @param x entero que sera agregado al arbol
 * @return DATO estructura que sera agregada al arbol
 */
DATO crearDatoEntero(int x) {
    DATO d;
    d.tipo = TIPO_INT;
    d.valor.entero = x;
    return d;
}

/**
 * @brief Crea un elemento del tipo DATO conteniendo un entero para poder guardarlo luego en el arbol
 * 
 * @param texto cadena de caracteres que sera agregado al arbol
 * @return DATO estructura que sera agregada al arbol
 */
DATO crearDatoCadena(char *texto) {
    DATO d;
    d.tipo = TIPO_STRING;
    strcpy(d.valor.cadena, texto);
    return d;
}

/**
 * @brief Agrega un nodo, de forma iterativa, al árbol
 * 
 * @param raiz puntero a la raíz del árbol
 * @param valor elemento a ser agregado al árbol
 * @return NODO puntero a la raíz del árbol considerando el nuevo nodo
 */
NODO agregarNodo(NODO raiz, DATO valor){
	NODO anterior, auxiliar;
	/* Crea el nuevo nodo */
	NODO nuevo = (NODO) malloc(sizeof(struct s_nodo));
	/* Setea los componentes de la estructura */
    nuevo->elemento = valor;

	nuevo->izquierdo = NULL;
	nuevo->derecho = NULL;

	/* Verifica si es el primer nodo */
	if (raiz == NULL){
		raiz = nuevo;
	} 
	else{
		/* De forma iterativa busca el lugar "correcto" del nuevo elemento */
		auxiliar = raiz;
        while (auxiliar != NULL){
            anterior = auxiliar;
            if (auxiliar->elemento.tipo == TIPO_INT) {
                if (valor.valor.entero < auxiliar->elemento.valor.entero){
                    auxiliar = auxiliar->izquierdo;
                }else{
                    auxiliar = auxiliar->derecho;
                }
            }
            else{
                if (strcmp(valor.valor.cadena, auxiliar->elemento.valor.cadena) < 0){
                    auxiliar = auxiliar->izquierdo;
                }else{
                    auxiliar = auxiliar->derecho;
                }                
            }
        }
        /* Verifica si será el hijo izquierdo o derecho */
        if (valor.tipo == TIPO_INT){
            if (valor.valor.entero < anterior->elemento.valor.entero){
                anterior->izquierdo = nuevo;
            }else{
                anterior->derecho = nuevo;
            }    
        }
        else{
            if (strcmp(valor.valor.cadena, anterior->elemento.valor.cadena) < 0){
                anterior->izquierdo = nuevo;
            }else{
                anterior->derecho = nuevo;
            }   
        }
	}
	return raiz;
}

/**
 * @brief imprime el contenido del nodo en funcion de su contenido
 * 
 * @param r direccion de memoria del nodo
 */
void imprimirElemento(NODO r){
    if (r->elemento.tipo == TIPO_INT){
        printf("%d ", r->elemento.valor.entero);
    }
    else{
        printf("%s ", r->elemento.valor.cadena);
    }    
}
/**
 * @brief Recorrido IN-ORDEN (IVD)
 * 
 * @param r puntero a la raíz del árbol a recorrer
 */
void inOrden(NODO r){
	if (r != NULL){
		inOrden(r->izquierdo); 
        imprimirElemento(r);		
		inOrden(r->derecho);
	}
}

/**
 * @brief Recorrido PRE-ORDEN (VID)
 * 
 * @param r puntero a la raíz del árbol a recorrer
 */
void preOrden(NODO r){
	if (r != NULL){
        imprimirElemento(r);
        preOrden(r->izquierdo);		
		preOrden(r->derecho);
	}
}

/**
 * @brief Recorrido POST-ORDEN (IDV)
 * 
 * @param r puntero a la raíz del árbol a recorrer
 */
void postOrden(NODO r){
	if (r != NULL){		
		postOrden(r->izquierdo);		
		postOrden(r->derecho);
        imprimirElemento(r);
	}
}

/**
 * @brief Buscar un elemento dentro del árbol que almacena valores enteros
 * 
 * @param raiz puntero al nodo raíz del árbol
 * @param elemento valor buscado dentro del árbol
 * @return int 1 en caso que exista y 0 en caso contrario
 */
int buscarEntero(NODO raiz, int elemento){
  if (raiz == NULL) return 0;
  else if (raiz->elemento.valor.entero < elemento)
    return buscarEntero(raiz->derecho, elemento);
  else if (raiz->elemento.valor.entero > elemento)
    return buscarEntero(raiz->izquierdo, elemento);
  else
    return 1;
}

/**
 * @brief Buscar un elemento dentro del árbol que almacena cadenas de caracteres
 * 
 * @param raiz puntero al nodo raíz del árbol
 * @param elemento valor buscado dentro del árbol
 * @return int 1 en caso que exista y 0 en caso contrario
 */
int buscarCadena(NODO raiz, char *elemento){
    if (raiz == NULL) return 0;
    if (strcmp(raiz->elemento.valor.cadena, elemento) == 0) return 1;
    else if (strcmp(raiz->elemento.valor.cadena, elemento) <= 0)
      return buscarCadena(raiz->derecho, elemento);
    else 
      return buscarCadena(raiz->izquierdo, elemento);
}

/**
 * @brief Buscar un elemento dentro del árbol 
 * 
 * @param raiz puntero al nodo raíz del árbol
 * @param target DATO buscado dentro del arbol
 * @return int 1 en caso que exista y 0 en caso contrario
 */
int buscar(NODO raiz, DATO target){
    if (target.tipo == TIPO_INT) return buscarEntero(raiz, target.valor.entero);
    return buscarCadena(raiz, target.valor.cadena);
}

/**
 * @brief Elimina un nodo del árbol
 * 
 * @param raiz puntero al nodo raíz del árbol
 * @param eliminado DATO a ser eliminado
 * @return NODO puntero al nodo raíz considerando la eliminación
 */
NODO remover(NODO raiz, DATO eliminado){
    if (eliminado.tipo == TIPO_INT){
	    return eliminarEntero(raiz, eliminado.valor.entero);
    }
    return eliminarCadena(raiz, eliminado.valor.cadena);
}

/**
 * @brief Une los nodos después de la elimiinación
 * 
 * @param izquierdo puntero al hijo izquierdo
 * @param derecho puntero al hijo derecho
 * @return NODO puntero al nodo que une a los hijos izquierdo y derecho
 */
NODO unir(NODO izquierdo, NODO derecho){
	NODO centro;
	if (izquierdo == NULL) return derecho;
	if (derecho == NULL) return izquierdo;
	/* Obtiene el elemento central */
	centro = unir(izquierdo->derecho, derecho->izquierdo);
	/* Re estructura */
	izquierdo->derecho = centro;
	derecho->izquierdo = izquierdo;
	return derecho;
}

/**
 * @brief Elimina un nodo del árbol que almacena valores enteros
 * 
 * @param raiz dirección de memoria del árbol al cual se le elimina un elemento
 * @param eliminado elemento a eliminar
 * @return NODO dirección de memoria del árbol considerando la eliminación
 */
NODO eliminarEntero(NODO raiz, int eliminado){
	if (raiz == NULL){
		return NULL;
	}
	/* Verifica si el elemento está en la actual raíz */
    if (raiz->elemento.valor.entero == eliminado){
		return unir(raiz->izquierdo, raiz->derecho);
    }
	/* Ya no estaba en el nodo raíz, por lo tanto, busca en el aub-árbol adecuado */
	if (raiz->elemento.valor.entero > eliminado){
		raiz->izquierdo = eliminarEntero(raiz->izquierdo, eliminado);
	}
	else{
		raiz->derecho = eliminarEntero(raiz->derecho, eliminado);
	}
	return raiz;
}

/**
 * @brief Elimina un nodo del árbol que almacena cadenas de caracteres
 * 
 * @param raiz dirección de memoria del árbol al cual se le elimina un elemento
 * @param eliminado elemento a eliminar
 * @return NODO dirección de memoria del árbol considerando la eliminación
 */
NODO eliminarCadena(NODO raiz, char *eliminado){
	if (raiz == NULL){
		return NULL;
	}
	/* Verifica si el elemento está en la actual raíz */
    if (strcmp(raiz->elemento.valor.cadena, eliminado) == 0){
		return unir(raiz->izquierdo, raiz->derecho);
    }
	/* Ya no estaba en el nodo raíz, por lo tanto, busca en el sub-árbol adecuado */
	if (strcmp(raiz->elemento.valor.cadena, eliminado) > 0){
		raiz->izquierdo = eliminarCadena(raiz->izquierdo, eliminado);
	}
	else{
		raiz->derecho = eliminarCadena(raiz->derecho, eliminado);
	}
	return raiz;
}

/**
 * @brief Retorna el elemento que se encuentra en la raíz del árbol
 * 
 * @param r puntero al nodo raíz del árbol, DEBE ser distinto de NULL
 * @return DATO elemento que se encuentra en la raíz
 */
DATO verRaiz(NODO r){
    return r->elemento;
}

/**
 * @brief Inserta un elemento de forma recursiva
 * 
 * @param a puntero al nodo raíz del árbol
 * @param elem elemento de tipo DATO que será agregado
 */
void insertar(NODO *a, DATO elem){
	if (*a == NULL){
    	*a = (NODO) malloc(sizeof(struct s_nodo));
        if (elem.tipo == TIPO_INT){
            (*a)->elemento.tipo = TIPO_INT;
            (*a)->elemento.valor.entero = elem.valor.entero;
        }
        else{            
            (*a)->elemento.tipo = TIPO_STRING;
            strcpy((*a)->elemento.valor.cadena, elem.valor.cadena);
        }
    	(*a)->izquierdo =  NULL;
    	(*a)->derecho = NULL;        
    }
    else{
        if (elem.tipo == TIPO_INT){
            insertarEntero(a, elem.valor.entero);
        }
        else{
            insertarCadena(a, elem.valor.cadena);
        }
    }
}

/**
 * @brief Inserta un entero en un arbol que almacena valores enteros
 * 
 * @param a dirección de memoria del árbol al cual se le inserta un elemento
 * @param elem elemento a insertar
 */
void insertarEntero(NODO *a, int elem){
	if (*a == NULL){
    	*a = (NODO) malloc(sizeof(struct s_nodo));
        (*a)->elemento.tipo = TIPO_INT;
        (*a)->elemento.valor.entero = elem;
    	(*a)->izquierdo =  NULL;
    	(*a)->derecho = NULL;
  	}
  	else if ((*a)->elemento.valor.entero <= elem){        
    	insertarEntero(&(*a)->derecho, elem);
    }
  	else{        
    	insertarEntero(&(*a)->izquierdo, elem);
    }
}

/**
 * @brief Inserta una cadena de caracteres en un arbol que almacena cadenas de caracteres
 * 
 * @param a dirección de memoria del árbol al cual se le inserta un elemento
 * @param elem elemento a insertar
 */
void insertarCadena(NODO *a, char *elem){
	if (*a == NULL){
    	*a = (NODO) malloc(sizeof(struct s_nodo));
        (*a)->elemento.tipo = TIPO_STRING;
        strcpy((*a)->elemento.valor.cadena, elem);
    	(*a)->izquierdo =  NULL;
    	(*a)->derecho = NULL;
  	}
  	else if (strcmp((*a)->elemento.valor.cadena, elem) <= 0){
    	insertarCadena(&(*a)->derecho, elem);
    }
  	else{
    	insertarCadena(&(*a)->izquierdo, elem);
        
    }
}
