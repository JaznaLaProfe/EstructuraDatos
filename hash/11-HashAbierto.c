/**
 * @file 11-HashAbierto.c
 * @author Jazna Meza Hidalgo
 * @brief implementacion de HASH abierto
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash.h"

/* Función principal */
int main(int argc, char *argv[]){
	if (argc != 3){
		printf("Faltan parametros\n");
		return -1;
	}
	int capacidad = atoi(argv[1]);
	int total = atoi(argv[2]);
	int i, aleatorio;	
	HASH tabla = crearTabla(capacidad);
	
	/* Simula las claves aleatorias */
	srand (time(NULL));
	printf("Tabla seteada\n");
	
	printf("Generando valores para la tabla hash...\n");
	for(i=1; i <= total; i++){		
		do{
			aleatorio = rand() % 50 + 1;
			/* Verifica que no exista */
			if (buscar(tabla, aleatorio) == -1){
				tabla = agregarClave(tabla, aleatorio);				
				break;
			}
		} while(1);
	}
	verTablaHash(tabla);
	printf("Tabla hash generada. Ver archivo hash.txt...\n");
	return 0;
}
