/* Definicion de tipo de datos */
typedef struct s_elemento{
    int numero;
    struct s_elemento *siguiente;
}*ELEMENTO;

/**
 * @brief crea un nuevo elemento con el valor indicado
 * @param valor elemento que sera creado
 * @return direccion de memoria del elemento creado
 */
ELEMENTO crearElemento(int valor){
    ELEMENTO e = (ELEMENTO) malloc(sizeof(struct s_elemento));
    e->numero = valor;
    return e;
}

/** 
 * @brief muestra en pantalla los datos del elemento
 * @param e elemento a ser visualizado
 */
void verElemento(ELEMENTO e){
    printf("{%d}\n", e->numero);
}