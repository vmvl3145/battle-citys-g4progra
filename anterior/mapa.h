#ifndef MAPA_H
#define MAPA_H

// Funciones relacionadas al manejo, generación, validación y almacenamiento de mapas para el proyecto Battle City.
// Incluye lectura desde archivo, generación aleatoria, posicionamiento de tanques, validación por DFS, y almacenamiento del mapa.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils.h"

// Funcion para verificar existencia de un archivo de mapa y cargarlo en memoria
int **leerArchivo(char *archivo,int filas, int columnas);

// Funcion para generar mapa aleatorio con bloques y caminos
int **generarMapa(int filas, int columnas);

// Funcion para generar tanques 1 y 2 en posiciones validas del mapa
void generarTanques(int **mapa);

// Funcion para realizar estudio de casillas libres (DFS) para validar mapa
void dfs(int x, int y, int **mapa, int **visitado, int filas, int columnas);

// Funcion para validar mapa generado o leido usando DFS
int validarMapa(int **mapa, int filas, int columnas);

// Funcion para generar un mapa completamente valido repetidamente hasta cumplir condiciones
int **generarMapaValido(int filas, int columnas);

// Funcion para almacenar el mapa en archivo "mapa.txt"
void almacenarMapa(int **mapa, int filas, int columnas, char *archivo);

#endif
