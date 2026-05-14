#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elemento.h"
#include "TAD-arbol.h"
#include "TAD-Fila.h"
#include "TAD-Pila.h"

NODO cargarNombres(char* nombre_archivo);
void clasificarNombres(NODO nombres, PILA* ultimos, FILA* primeros, DATO criterio);

int main(int argc, char *argv[]){    
    FILA prioritarios = crearFila();
    PILA no_prioritarios = crearPila();
    /* Etapa 1 */
    NODO nombres = cargarNombres(argv[1]);
    printf("Primer elemento: %s\n",verRaiz(nombres).valor.cadena);

    /* Etapa 2 */
    printf("\nClasificando nombres\n");
    DATO criterio = crearDatoCadena(argv[2]);
    clasificarNombres(nombres, &no_prioritarios, &prioritarios, criterio);

    printf("\nPrimer elemento accesible Estructura A: %s\n", verRaiz(nombres).valor.cadena);
    printf("\nPrimer elemento accesible Estructura B: %s\n", verTope(no_prioritarios)->valor.valor.cadena);
    printf("\nPrimer elemento accesible Estructura C:%s\n", verPrimero(prioritarios)->valor.valor.cadena);
    return 0;
}

NODO cargarNombres(char* nombre_archivo){
    FILE *archivo;
    NODO arbol = NULL;
    char linea[500];

    archivo = fopen(nombre_archivo, "r");

    while(fgets(linea, sizeof(linea), archivo) != NULL){
        arbol = agregarNodo(arbol, crearDatoCadena(linea));
    }

    return arbol;
}

void clasificarNombres(NODO nombres, PILA* ultimos, FILA* primeros, DATO criterio){
    if (nombres != NULL){
        clasificarNombres(nombres->izquierdo, ultimos, primeros, criterio);
        if (strcmp(verRaiz(nombres).valor.cadena, criterio.valor.cadena) > 0){
            insert(primeros, crearElementoCadena(verRaiz(nombres).valor.cadena));
        }
        else{
            push(ultimos, crearElementoCadena(verRaiz(nombres).valor.cadena));
        }
        clasificarNombres(nombres->derecho, ultimos, primeros, criterio);
    }
}