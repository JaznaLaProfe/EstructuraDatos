#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "elemento.h"
#include "TAD-Fila.h"
#include "TAD-Pila.h"

void filtrar(PILA origen, FILA *resultado);

int main(int argc, char *argv[]){
    /* Verificar la cantidad de parametros */
    if (argc != 4){
        printf("Uso correcto es: %s n a b\n", argv[0]);
        return 0;
    }
    /* Obtiene los valroes de los parámetros */
    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    int numero;
    srand(time(NULL));
    PILA p = crearPila();
    FILA f = crearFila();
    /* Generar los aleatorios */
    for(int i = 1; i <= n; i++){
        /* Genera el valor aleatorio */
        numero = rand() % (b - a + 1) + a;
        printf("Valor generado : %d\n", numero);
        push(&p, crearElemento(numero));
    }
    /* Llamada a la funcion */
    filtrar(p, &f);
    /* Obtiene el primer elemento accesible */
    printf("Primer elemento accesible es %d\n", verPrimero(f)->numero);
    /* Muestra el contenido del resultado */
    verFila(f);
    return 1;
}

void filtrar(PILA origen, FILA *resultado){
    while(!isEmpty(origen)){
        /* Verifica la paridad de acuerdo a requerimiento */
        if (verTope(origen)->numero % 2 == 0){
            insert(resultado, crearElemento(verTope(origen)->numero));
        }
        pop(&origen);
    }
}