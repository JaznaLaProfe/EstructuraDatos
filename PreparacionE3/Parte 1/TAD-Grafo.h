#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES 100

/* Define la matriz de adyacencia para representar un grafo */
typedef struct s_matriz{
	int es_dirigido;
	int total_vertices;
	int matriz[MAX_VERTICES][MAX_VERTICES];	
	char nombre_vertices[MAX_VERTICES];
} MATRIZ_ADYACENCIA;

/* Define las estructuras para la lista de adyacencia */
typedef struct s_nodo{
	char vertice;
	struct s_nodo *siguiente;
} *NODO_VERTICE;

typedef struct s_elemento{
	char vertice;
	struct s_nodo *conectado;
	struct s_elemento *siguiente;
} *NODO_ADYACENCIA;

typedef struct s_lista{
	int es_dirigido;
	NODO_ADYACENCIA lista;
} LISTA_ADYACENCIA;

/* Prototipo de funciones para trabajar con la matriz de adyacencia */
MATRIZ_ADYACENCIA crearMatrizGrafo(char *, char *, int);
void verMatrizGrafo(MATRIZ_ADYACENCIA);
int getIndice(char *, int, char);

/* Prototipo de funciones para trabajar con la lista de adyacencia */
LISTA_ADYACENCIA crearListaAdyacencia(char *, char*, int);
void verListaAdyacencia(LISTA_ADYACENCIA);
LISTA_ADYACENCIA agregaArista(LISTA_ADYACENCIA, char, char);

/**
 * @brief Crear la matriz de adyacencia
 * 
 * @param fvertices nombre del archivo donde estan los vertices
 * @param faristas nombre del archivo donde estan las aristas
 * @param es_dirigido 1 en caso de un grafo dirigido y 0 si es un grafo no dirigido
 * @return MATRIZ_ADYACENCIA matriz de adyacencia del grafo
 */
MATRIZ_ADYACENCIA crearMatrizGrafo(char *fvertices, char *faristas, int es_dirigido){
	MATRIZ_ADYACENCIA m;	
    
	FILE *archivo;
    int total_vertices, i, j, indice_inicio, indice_fin;

    char inicio, fin, vertice;	

    /* Obtiene los vertices del grafo */
    archivo = fopen(fvertices, "r");
    total_vertices = 0;	
    while (!feof(archivo)){
        fscanf(archivo, "%c\n", &vertice);   		
        m.nombre_vertices[total_vertices] = vertice;              
        total_vertices += 1;
    }
	fclose(archivo);
	
	m.total_vertices = total_vertices;	
	m.es_dirigido = es_dirigido;

	for(i=0; i < total_vertices; i++){
		for(j=0; j < total_vertices; j++){
			m.matriz[i][j] = 0;			
		}
	}
    /* Ahora carga las aristas */
    archivo = fopen(faristas, "r");
	
	while (!feof(archivo)){	
		fscanf(archivo, "%c-%c\n", &inicio, &fin);			
		indice_inicio = getIndice(m.nombre_vertices, total_vertices, inicio);
		indice_fin = getIndice(m.nombre_vertices, total_vertices, fin);
		//printf("\tArista %c-%c en [%d,%d]\n", inicio, fin, indice_inicio, indice_fin);
		m.matriz[indice_inicio][indice_fin] = 1;
		if (!es_dirigido){
			m.matriz[indice_fin][indice_inicio] = 1;
			printf("Repite la arista\n");
		}
	}	
	fclose(archivo);	
	return m;
}

/**
 * @brief Mostrar el grafo representado con la matriz de adyacencia
 * 
 * @param g grafo a ser mostrado
 */
void verMatrizGrafo(MATRIZ_ADYACENCIA g){
	int i, j;
	/* Imprime el nombre de los vertices */
	printf("<< MATRIZ DE ADYACENCIA >>\n\nGrafo %s\n", (g.es_dirigido?"DIRIGIDO\n":"NO DIRIGIDO\n"));
	printf("\t");
	for(i=0; i < g.total_vertices; i++){
		printf("%c\t", g.nombre_vertices[i]);
	}
	printf("\n\t");
	for(i=0; i < g.total_vertices; i++){
		printf("-\t");
	}
	printf("\n");
	for(i=1; i <= g.total_vertices; i++){
		printf("%c\t", g.nombre_vertices[i-1]);
		for(j=0; j < g.total_vertices; j++){			
			printf("%d\t", g.matriz[i-1][j]);
		}
		printf("\n");
	}
}

/**
 * @brief Get the Indice object. Retornar el indice de un vertice
 * 
 * @param cadena nombre de los vertices
 * @param numero_vertices cantidad de vertices existentes
 * @param c vertice buscado
 * @return int indice del vertice (-1 en caso de que no exista)
 */
int getIndice(char *cadena, int numero_vertices, char c){
	int i;
	for(i=0; i < numero_vertices; i++){
		if (cadena[i] == c) return i;
	}
	return -1;
}

/**
 * @brief Crear la lista de adyacencia
 * 
 * @param fvertices nombre del archivo donde estan los vertices
 * @param faristas nombre del archivo donde estan las aristas
 * @param es_dirigido 1 en caso de un grafo dirigido y 0 si es un garfo no dirigido
 * @return LISTA_ADYACENCIA lista de adyacencia del grafo
 */
LISTA_ADYACENCIA crearListaAdyacencia(char *fvertices, char *faristas, int es_dirigido){
	LISTA_ADYACENCIA lista_ad;
	FILE *archivo;
	char x_vertice, inicio, fin;
	NODO_ADYACENCIA vertice, ultimo;
    /* Obtiene los vertices del grafo */
	lista_ad.es_dirigido = es_dirigido;
	lista_ad.lista = NULL;
	
    archivo = fopen(fvertices, "r");
    while (!feof(archivo)){
        fscanf(archivo, "%c\n", &x_vertice);   
        vertice = (NODO_ADYACENCIA) malloc(sizeof(struct s_elemento));     
		vertice->vertice = x_vertice;
		vertice->conectado = NULL;
		vertice->siguiente = NULL;	
		if (lista_ad.lista == NULL){
			lista_ad.lista = vertice;
			ultimo = lista_ad.lista;
		}
		else{
			ultimo->siguiente = vertice;
			ultimo = ultimo->siguiente;
		}			     
    }
	fclose(archivo);	
	/* Ahora carga las aristas */
	archivo = fopen(faristas, "r");
	while (!feof(archivo)){	
		fscanf(archivo, "%c-%c\n", &inicio, &fin);	
		/* Agrega las aristas a la lista de adyacencia */		
		lista_ad = agregaArista(lista_ad, inicio, fin);		
		if (es_dirigido && inicio != fin) lista_ad =  agregaArista(lista_ad, fin, inicio);		
	}	
	return lista_ad;
}

/**
 * @brief Agrega las aristas a la lista de adyacencia
 * 
 * @param lista lista de adyacencia que sera modificada
 * @param inicio extremo inicial de la arista
 * @param fin extremo final de la arista	
 */
LISTA_ADYACENCIA agregaArista(LISTA_ADYACENCIA x_lista, char inicio, char fin){
	NODO_ADYACENCIA auxiliar;
	NODO_VERTICE nodo_fin, auxiliar_vertice;

	auxiliar = x_lista.lista;
	nodo_fin = (NODO_VERTICE) malloc(sizeof(struct s_nodo));
	nodo_fin->vertice = fin;	
	nodo_fin->siguiente = NULL;
	/* Busca el vértice de inicio */	
	while(auxiliar->vertice != inicio){
		auxiliar = auxiliar->siguiente;
	}
	/* Asocia el extremo */
	if (auxiliar->conectado == NULL){
		auxiliar->conectado = nodo_fin;
	}
	else{		
		auxiliar_vertice = auxiliar->conectado;
		while (auxiliar_vertice->siguiente != NULL){
			auxiliar_vertice = auxiliar_vertice->siguiente;
		}	
		auxiliar_vertice->siguiente = nodo_fin;
	}	
	return x_lista;
}

/**
 * @brief Mostrar la lista de adyacencia
 * 
 * @param lista lista de adyacencia del grafo
 */
void verListaAdyacencia(LISTA_ADYACENCIA x_lista){
	NODO_ADYACENCIA auxiliar = x_lista.lista;
	NODO_VERTICE aux_vertice;

	printf("<< LISTA DE ADYACENCIA >>\nGrafo %s\n", (x_lista.es_dirigido?"DIRIGIDO":"NO DIRIGIDO"));
	while(auxiliar != NULL){
		printf("\t%c ==> ", auxiliar->vertice);
		aux_vertice = auxiliar->conectado;
		while (aux_vertice != NULL){
			printf("%c", aux_vertice->vertice);
			aux_vertice = aux_vertice->siguiente;
			printf("%s", (aux_vertice == NULL?" ":" -> "));
		}		
		printf("\n");
		auxiliar = auxiliar->siguiente;
	}
	printf("\n");
}
