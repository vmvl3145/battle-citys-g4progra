#include "utils.h"

// Funcion para liberar memoria dinamica utilizada por una matriz
void liberaMemoria(int **matriz, int filas){
    if (matriz == NULL) return; // seguridad: si no hay memoria pedida, nada que liberar

    for (int i = 0; i < filas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

// Funcion para reservar memoria dinamica destinada a matrices
// int conCeros sirve para verificar forma de inicializar la matriz -- 1: inicializar lleno de ceros
//                                                             -- 0: inicializar sin ceros
int **reservaMemoria(int filas, int columnas, int conCeros){

    int **matriz = malloc(filas * sizeof(int*));
    if (matriz == NULL){    // En caso de que ocurra un error al pedir memoria, reportamos
        printf("Error. No se ha podido reservar memoria para filas en el mapa.\n");
        return NULL;
    }

    if (conCeros == 1){          // Inicializacion llena de ceros
        for (int i = 0; i < filas; i++){
            matriz[i] = calloc(columnas, sizeof(int));

            if (matriz[i] == NULL){     // Reporte de error
                printf("Error. No se ha podido reservar memoria para columnas en el mapa.\n");
                // Liberamos solo las filas asignadas hasta ahora
                liberaMemoria(matriz, i);
                return NULL;
            }
        }
    } else {                // Inicializacion normal
        for (int i = 0; i < filas; i++){
            matriz[i] = malloc(columnas * sizeof(int));

            if (matriz[i] == NULL){     // Reporte de error
                printf("Error. No se ha podido reservar memoria para columnas en el mapa.\n");
                // Liberamos solo las filas asignadas hasta ahora
                liberaMemoria(matriz, i);
                return NULL;
            }
        }
    }

    return matriz;
}

// Funcion para imprimir matriz en pantalla, util para depuracion y visualizacion
void imprimirMapa(int **matriz, int filas, int columnas){
    if (matriz == NULL) {
        printf("(matriz nula)\n");
        return;
    }
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}
