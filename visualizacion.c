#include <stdio.h>
#include "visualizacion.h"

#define RST  "\x1b[0m"
#define ROJO "\x1b[31m"
#define VERD "\x1b[32m"
#define AMAR "\x1b[33m"
#define GRIS "\x1b[90m"
#define AZUL "\x1b[34m"

void visualizarMapa(int **mapa, int filas, int columnas) {
    printf("\033[H\033[J"); // Limpia la consola
    printf(AZUL "=== BATTLE CITY ===\n\n" RST);

    for (int i = 0; i < filas; i++) {
        printf("   "); 
        for (int j = 0; j < columnas; j++) {
            switch (mapa[i][j]) {
                case 0: printf("  "); break;                    // Vacio
                case 1: printf(AMAR "▒▒" RST); break;           // Ladrillo
                case 2: printf(GRIS "██" RST); break;           // Acero
                case 3: printf(VERD "T1" RST); break;           // Jugador 1
                case 4: printf(ROJO "T2" RST); break;           // Jugador 2
                default: printf("??"); // si hay algo q no es válido, nunca se sabe
            }
        }
        printf("\n");
    }
    printf("\n" AZUL "----------------------------------" RST "\n");
}