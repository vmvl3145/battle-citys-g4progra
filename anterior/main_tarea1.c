#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "utils.h"

#define FILAS 13
#define COLUMNAS 13

int main(){

    char *archivo = "mapa.txt";
    int **mapa = leerArchivo(archivo, FILAS, COLUMNAS);

    // Si no hay un archivo "mapa.txt", se genera un mapa valido desde el codigo
    if (mapa == NULL){
        printf("Generando mapa aleatorio...\n");
        mapa = generarMapaValido(FILAS,COLUMNAS);
    
    // Si hay un archivo "mapa.txt", se valida que sea correcto
    } else {
        printf("Archivo de mapa encontrado!\nValidando archivo...\n");

        // Validamos mapa leido desde archivo
        if (!validarMapa(mapa,FILAS,COLUMNAS)){
            printf("Mapa invalido.\nGenerando mapa aleatorio...\n");

            liberaMemoria(mapa,FILAS);
            mapa = generarMapaValido(FILAS,COLUMNAS);

        } else {
            printf("Mapa valido!\n");
        }
    }

    printf("\nMapa final, 0: Despejada, 1: Destructible, 2: Indestructible, 3: Tanque 1, 4: Tanque 2\n\n");

    imprimirMapa(mapa, FILAS, COLUMNAS);
    almacenarMapa(mapa,FILAS,COLUMNAS,archivo);
    liberaMemoria(mapa,FILAS);
    
    return 0;
}
