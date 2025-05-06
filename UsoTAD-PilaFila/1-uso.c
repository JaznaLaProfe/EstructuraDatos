/**
 * Leer desde la linea de comandos 2 valores: uno que represente
 * la cantidad de valores aleatorios a generar y otro: el umbral 
 * maximo que deben tener los valores generados.
 * 
 * El valor minimo de los valores generados sera 1
 * 
 * Los valores pares generados se deben guardar en una pila y
 * los valores impares generados se deben guardar en una fila
 * 
 * Finalmente, mostrar el contenido de ambas estructuras
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "elemento.h"
#include "TAD-Fila.h"
#include "TAD-Pila.h"

int main(int argc, char *argv[]){
    int numero, n, umbral;
    PILA mi_pila = crearPila();
    FILA mi_fila = crearFila();

    srand(time(NULL));
    if (argc == 3){
        /* Rescata los valores del la linea de comandos */
        n = atoi(argv[1]);
        umbral = atoi(argv[2]);
        /* Generar los valores aleatorios */
        for(int i=1; i <= n; i++){
            numero = rand() % umbral + 1;
            printf("Valor %d generado es %d\n", i, numero);
            /* Verifica la paridad del valor generado */
            if (numero % 2 == 0){
                push(&mi_pila, crearElemento(numero));
            }
            else{
                insert(&mi_fila, crearElemento(numero));
            }
        }
        /* Muestra el contenido de la pila */
        printf("Contenido de la pila:\n");
        verPila(mi_pila);
        /* Muestra el contenido de la fila */
        printf("Contenido de la fila:\n");
        verFila(mi_fila);

    }
    else{
        printf("Uso incorrecto!!!!\n");
    }
    return 1;
}


