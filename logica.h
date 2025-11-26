#ifndef LOGICA_H
#define LOGICA_H

typedef struct {
    int fila; // 'row'
    int col;  // 'col'
    int dir;  // 0=up, 1=down, 2=left, 3=right
    int vida; // hp
} Tanque;

// Estructura interna (shoot)
struct shoot {
    int col;
    int row;
};

// Inicializa las estructuras buscando en el mapa
void inicializarTanques(int **mapa, int filas, int cols, Tanque *t1, Tanque *t2);
//funcion de movimiento (moveTank)
void moverTanque(int **mapa, int filas, int cols, Tanque *t1, Tanque *t2, int turn, char moveDir);
//funcion de disparo (shoot)
void disparar(int **mapa, int filas, int cols, int sRow, int sCol, int sDir, int shooter, Tanque *t1, Tanque *t2);
//funcion de respawn (placeRandomPos)
Tanque reubicarTanque(int **mapa, int filas, int cols, Tanque t);

// Verifica ganador
int verificarGanador(Tanque t1, Tanque t2);

#endif
