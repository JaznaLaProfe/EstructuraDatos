#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TAD-arbol.h"
#include "TAD-Fila.h"

FILA cargarPalabras(char *nombre_archivo);

/* Funcion solicitada en la clase anterior */
NODO crearArbol(FILA palabras);

/* Funciones entregadas */
int levenshtein_distance(const char *s1, const char *s2);

/* Funcion solicitada en la evaluacion */
void obtiene_menores_umbral(NODO r, int umbral, char *buscada, FILA *resultado, FILA *distancias);

/* Funcion principal */
int main(int argc, char *argv[]){
    return 1;
}

/**
 * @brief carga un conjunto de palabras desde un archivo
 * @param nombre_archivo contiene la cadena de caracteres con el nombre del archivo
 * @return FILA conteniendo las palabras leidas desde el archivo
 */
FILA cargarPalabras(char *nombre_archivo){
    FILE *archivo;
    FILA fila_palabras = crearFila();
    char palabra[100];

    /* Obtiene los numeros del archivo */
    archivo = fopen(nombre_archivo, "r");
    
    while (!feof(archivo)){
        fscanf(archivo, "%s\n", palabra);
        insert(&fila_palabras, crearElementoCadena(palabra));
    }
    return fila_palabras;
}

/**
 * @brief crea un arbol con las palabras contenidas en la fila
 * @param palabras fila conteniendo una coleccion de palabras
 * @return NODO direccion de memoria de un ABB conteniendo la coleccion de palabras 
 */
NODO crearArbol(FILA palabras){
    NODO mis_palabras = NULL;
    while (!empty(palabras)){        
        mis_palabras = agregarNodo(mis_palabras, crearDatoCadena(verPrimero(palabras)->valor.valor.cadena));
        extract(&palabras);
    }
    return mis_palabras;
}

int min(int a, int b, int c) {
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}
/**
 * @brief Retorna la distancia que hay entre 2 palabras
 * @param s1 primera cadena de caracteres
 * @param s2 segunda cadena de caracteres
 * @return int distancia entre las palabras
 */

int levenshtein_distance(const char *s1, const char *s2) {
    int longitud_p1 = strlen(s1);
    int longitud_p2 = strlen(s2);
    int matrix[longitud_p1 + 1][longitud_p2 + 1];

    /* Inicializar la matriz */
    for (int i = 0; i <= longitud_p1; i++) {
        for (int j = 0; j <= longitud_p2; j++) {
            if (i == 0) {
                matrix[i][j] = j;
            } else if (j == 0) {
                matrix[i][j] = i;
            } else {
                matrix[i][j] = 0; // Inicializar
            }
        }
    }

    /* Calcular la distancia */
    for (int i = 1; i <= longitud_p1; i++) {
        for (int j = 1; j <= longitud_p2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1];
            } else {
                matrix[i][j] = 1 + min(matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]);
            }
        }
    }
    return matrix[longitud_p1][longitud_p2];
}

/**
 * @brief Calcula la cantidad de palabras cuya distancia es menor al umbral
 * @param r direccion de memoria a la raiz del arbol
 * @param k cantidad de palabras mas cercanas que se necesitan
 * @param resultado direccion de memoria de la fila que guarda las palabras seleccionadas
 * @param distancias direccion de memoria de la fila que contiene las distancias de todas las palabras
 */
void obtiene_menores_umbral(NODO r, int umbral, char *buscada, FILA *resultado, FILA *distancias){
    /* Escriba su codigo aca */
}