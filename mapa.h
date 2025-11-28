#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// Funciones de Memoria
void liberaMemoria(int **matriz, int filas);
int **reservaMemoria(int filas, int columnas, int conCeros);


// Funciones de Mapa
int **generarMapa(int filas, int columnas);
void generarTanques(int **mapa);
void dfs(int x, int y, int **mapa, int **visitado, int filas, int columnas);
int validarMapa(int **mapa, int filas, int columnas);
int **generarMapaValido(int filas, int columnas);
void imprimirMapa(int **mapa, int filas, int columnas); // Version numerica (debug)


// Funciones de lectura y almacenamiento del mapa
int **leerArchivo(char *archivo,int filas, int columnas);
void almacenarMapa(int **mapa, int filas, int columnas, char *archivo);
void guardarEstado(int **mapa, int filas, int columnas);
int **cargarEstado(int filas, int columnas);


#endif
