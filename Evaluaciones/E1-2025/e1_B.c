#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "elemento.h"
#include "TAD-Fila.h"
#include "TAD-Pila.h"

void transformar(FILA origen, FILA *resultado);

int main(int argc, char *argv[]){
    /* Verifica la cantidad de parametros */
    if (argc != 4){
        printf("Uso correcto es: %s n a b\n", argv[0]);
        return 0;
    }
    /* Rescato los parametros desde la linea de comandos */
    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    int numero;
    FILA fx = crearFila(), fy = crearFila();

    srand(time(NULL));
    for(int i =1; i<= n; i++){
        /* Generar el valor aleatorio */
        numero = rand() % (b - a + 1) + a;
        printf("Valor generado %d\n", numero);
        /* Agregar el elemento a la estructura de origen */
        insert(&fx, crearElemento(numero));        
    }
    /* Llamada a la función */
    transformar(fx, &fy);
    printf("Primer elemento accesible es %d\n", verPrimero(fy)->numero);
    /* Mostrar el contenido del resultado */
    verFila(fy);
    return 1;
}

void transformar(FILA origen, FILA *resultado){
    while(!empty(origen)){
        insert(resultado, crearElemento(verPrimero(origen)->numero));
        extract(&origen);
    }
}