#include <stdio.h>
#include <stdlib.h>
/* Estructuras de datos */
typedef struct s_lista{
	int valor;
	struct s_lista *siguiente;
} *ELEMENTO;

typedef struct s_tabla{
	int clave;
    int valor;
    /* Esto es el uso estructura adicional para implementar hashing abierto */
	ELEMENTO entradas;
} CLAVE;

/* Representa la tabla HASH */
typedef struct s_hash{
    int capacidad;
    CLAVE claves[100];
    int libre[100];
} HASH;

/* Prototipo de funciones */
int hash(int, int);
void verTablaHash(HASH);
HASH crearTabla(int);
HASH agregarClave(HASH, int);
int buscar(HASH, int);

/**
 * @brief Retornar el codigo HASH
 * 
 * @param k Clave a la cual se aplica la funcion
 * @return int Codigo hash asociado a la clave
 */
int hash(int k, int capacidad){
	return k % capacidad;
}

/**
 * @brief Ver la tabla HASH
 * 
 * @param tabla Tabla hash que se imprime 
 */
void verTablaHash(HASH tabla){
	int indice;
	ELEMENTO auxiliar;
    FILE *archivo_hash = fopen("hash.txt", "w");
	fprintf(archivo_hash, "\n ** TABLA HASH **\n");
	for(indice=0; indice < tabla.capacidad; indice++){		
		if (tabla.claves[indice].entradas == NULL){
			if (tabla.libre[indice]){
				fprintf(archivo_hash, "%d | {-}\n", tabla.claves[indice].clave);
			}
			else{
				fprintf(archivo_hash, "%d | {%d}\n", tabla.claves[indice].clave, 
            	tabla.claves[indice].valor);	
			}
		}
		else{
			fprintf(archivo_hash, "%d | {%d,", tabla.claves[indice].clave,
            tabla.claves[indice].valor);
			/* Muestra las entradas de la clave */
			auxiliar = tabla.claves[indice].entradas;
			while (auxiliar != NULL){
				fprintf(archivo_hash, "%d", auxiliar->valor);
				auxiliar = auxiliar->siguiente;
				fprintf(archivo_hash,"%s",(auxiliar != NULL?",":"}\n"));
			}
		}
	}
    fclose(archivo_hash);
}

/**
 * @brief Setear la tabla HASH
 * 
 * @param tabla Tabla hash a setear
 */
HASH crearTabla(int capacidad){
	int indice;
    HASH tabla;
    tabla.capacidad = capacidad;
	for(indice=0; indice < tabla.capacidad; indice++){
		tabla.claves[indice].clave = indice;
        tabla.libre[indice] = 1;
		tabla.claves[indice].entradas = NULL;
	}
    return tabla;
}

/**
 * @brief Agregar entrada a la tabla HASH
 * 
 * @param tabla Tabla hash a la cual se agrega la entrada
 * @param valor Entrada que se agrega a la tabla
 */
HASH agregarClave(HASH tabla, int valor){
	int u_hash;
	ELEMENTO auxiliar;
	/* Obtiene el codigo hash */
	u_hash = hash(valor, tabla.capacidad);
    if (tabla.libre[u_hash]){
        tabla.claves[u_hash].valor = valor;
		tabla.libre[u_hash] = 0;
        return tabla;
    }
	ELEMENTO nuevo = (ELEMENTO) malloc(sizeof(struct s_lista));
	nuevo->valor = valor;
	nuevo->siguiente = NULL;

	if (tabla.claves[u_hash].entradas == NULL){
		tabla.claves[u_hash].entradas = nuevo;
	}
	else{		
		auxiliar = tabla.claves[u_hash].entradas;
		while(auxiliar->siguiente != NULL){
			auxiliar = auxiliar->siguiente;
		}
		auxiliar->siguiente = nuevo;
	}
    return tabla;
}

/**
 * @brief Buscar entrada a la tabla HASH
 * 
 * @param tabla Tabla hash donde se busca
 * @param target Entrada que se busca en la tabla
 * @return int 
 * 		1 : en caso de exito
		-1 : en caso de fracaso
 */
int buscar(HASH tabla, int target){	
	ELEMENTO auxiliar;
    int x_hash = hash(target, tabla.capacidad);
	auxiliar = tabla.claves[x_hash].entradas;
	/* Verifica que el codigo hash tenga al menos un elemento */
	if (tabla.libre[x_hash] == 1) return -1;
	if (tabla.claves[x_hash].valor == target) return 1;
    /* Va a buscar en la lista de colisiones */
	while(auxiliar != NULL){
		if (auxiliar->valor == target) return 1;
		auxiliar = auxiliar->siguiente;
	}
	return -1;	
}