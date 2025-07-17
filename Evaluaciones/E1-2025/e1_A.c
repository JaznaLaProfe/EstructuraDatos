#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "elemento.h"
#include "TAD-Fila.h"
#include "TAD-Pila.h"

void procesar(PILA origen, FILA *resultado);

int main(int argc, char *argv[]){
    /* VErificar la cantidad de parámetros */
    if (argc != 4){
        printf("Uso correcto es: %s n a b\n", argv[0]);
        return 0;
    }
    int n, inicial, final, numero;
    /* Rescata los valores desde la linea de comandos */
    n = atoi(argv[1]);
    inicial = atoi(argv[2]);
    final = atoi(argv[3]);
    srand(time(NULL));
    /* Crear el entorno para ejecutar la funcion */
    PILA p = crearPila();
    FILA f = crearFila();
    for(int i =1; i <= n; i++){
        numero = rand() % (final - inicial + 1) + inicial;
        printf("Valor generado es %d\n", numero);
        push(&p, crearElemento(numero));
    }
    /* Llamada a la funcion */
    procesar(p, &f);
    /* Acceder al primer elemento de la variable f */
    printf("Primer elemento accesible es %d\n", verPrimero(f)->numero);
    /* Muestra el contenido del resultado */
    verFila(f);
    return 1;
}

void procesar(PILA origen, FILA *resultado){
    while(!isEmpty(origen)){
        insert(resultado, crearElemento(verTope(origen)->numero));
        pop(&origen);
    }
}