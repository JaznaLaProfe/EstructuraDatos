#include "max-heap.h"

MAX_HEAP* cargarDatos(char *, int);

int main(int argc, char *argv[]) {

    char *fuente_datos = argv[1];
    int capacidad = atoi(argv[2]);
    int eliminados = atoi(argv[3]);

    MAX_HEAP *heap = cargarDatos(fuente_datos, capacidad);
    /* Muestra el heap por niveles */
    printf("HEAP original\n\n");
    verPorNivelesMaxHeap(heap);
    printf("Eliminando maximos ...\n");
    /* Extra los valores minimos que se indican en el parametro */
    for(int i=1; i <= eliminados; i++){
        printf("\tMaximo %d es %d\n", i, extraerMaximo(heap));    
    }
    /* Muestra el heap por niveles */
    printf("HEAP Despues de eliminar los %d mayores\n\n", eliminados);
    verPorNivelesMaxHeap(heap);
    return 0;
}

/**
 * @brief Crea un HEAP a partir de los datos contenidos en el archivo 
 * considerando la capacidad maxima entregada
 * 
 * @param nombre nombre del archivo a cargar
 * @param maximaCapacidad cantidad maxima de elementos que tendra el HEAP
 * 
 * @return puntero al HEAP creado
 */
MAX_HEAP* cargarDatos(char *nombre, int maximaCapacidad){
    MAX_HEAP *heap;
    FILE *archivo = fopen(nombre, "r");
    int valor;
    /* Crea un heap con la maxima capacidad */
    heap = createMaxHeap(maximaCapacidad);
    printf("Cargando datos ...\n");
    while (!feof(archivo)){
        fscanf(archivo,"%d", &valor);
        if (insertarMaxHeap(heap, valor)) printf("\t%d ha sido incorporado con extio a la estructura\n", valor);
        else printf("\t%d tuvo problemas para ser incorporado a la estructura\n", valor);
    }
    
    fclose(archivo);
    return heap;
}