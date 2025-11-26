#ifndef UTILS_H
#define UTILS_H

// Funciones de utilidad general para diversas etapas del proyecto

#include <stdio.h>
#include <stdlib.h>

// Funcion para liberar memoria dinamica utilizada por una matriz
void liberaMemoria(int **matriz, int filas);

// Funcion para reservar memoria dinamica destinada a matrices
int **reservaMemoria(int filas, int columnas, int conCeros);

// Funcion para imprimir matriz en pantalla representativa del mapa
void imprimirMapa(int **matriz, int filas, int columnas);

#endif
