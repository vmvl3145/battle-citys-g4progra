#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mapa.h"
#include "utils.h"

#define FILAS 13
#define COLUMNAS 13

// Funcion para verificar existencia de un archivo de mapa
int **leerArchivo(char *archivo,int filas, int columnas){
    FILE *fmapa = fopen(archivo,"r");

    // Si el archivo no existe, retornamos NULL directamente para que el programa despues genere por si solo el mapa
    if (fmapa == NULL){
        printf("Archivo de mapa \"mapa.txt\" no encontrado.\n");
        return NULL;
    }

    // En caso de que exista, solicitamos memoria dinamica para almacenarlo y con un ciclo for vamos almacenando los datos del mapa escritos en el programa
    int **mapa = reservaMemoria(filas,columnas,0);

    // Lectura del mapa, las dimensiones de este seran de 13x13 por lo que establecemos un contador de valores leidos ante posibilidad de que se ingrese una dimension menor
    int leidos = 0;
    int c_tanque1 = 0;  // Aparte verificamos que en la entrada del archivo exista un tanque por jugador
    int c_tanque2 = 0;
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){


            if (fscanf(fmapa,"%d",&mapa[i][j]) == 1) 
                leidos++; // Como fscanf leera solo un parametro, ira devolviendo "1" por cada lectura correcta
            else 
                break; // Si devuelve otro valor, sera EOF si termino la lectura del archivo o 0 si encontro texto no numerico (los espacios no se consideran, la funcion en "%d" directamente los ignora)


            // Validamos que el archivo posea valores correctos [0,4]
            if (mapa[i][j] < 0 || mapa[i][j] > 4){
                printf("Valores fuera de rango encontrados en (%d,%d) = %d. Descartando mapa\n",i,j,mapa[i][j]);
                fclose(fmapa);
                return NULL;
            }

            if (mapa[i][j] == 3) 
                c_tanque1++;
            else if (mapa[i][j] == 4) 
                c_tanque2++;
        }
    }

    fclose(fmapa);

    // Verificamos dimensiones del mapa y cantidad correcta de tanques
    if (leidos < filas*columnas){
        printf("Archivo con dimensiones incorrectas, %d datos leidos de un total de %d esperados\n",leidos, filas*columnas);
        liberaMemoria(mapa,filas);
        return NULL;
    } else if (c_tanque1 != 1 || c_tanque2 != 1){
        printf("Archivo con cantidad incorrecta de tanques.\n");
        liberaMemoria(mapa,filas);
        return NULL;
    }

    return mapa;
}


// Funcion para generar mapa aleatorio
int **generarMapa(int filas, int columnas){
    srand(time(NULL));

    int **mapa = reservaMemoria(filas, columnas, 0);

    // Valor 0: Celda desplazable
    // Valor 1: Bloque destructible
    // Valor 2: Bloque indestructible
    // Valor 3: Tanque 1
    // Valor 4: Tanque 2


    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){

            // Delimitamos el mapa con bordes indestructibles
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1){
                mapa[i][j] = 2;
            } else {
                int prob = rand()%100;  // Para generar el mapa aleatoriamente, utilizaremos un numero entre [0,100] para escoger el estado de cada celda 
                
                if (prob <= 60) mapa[i][j] = 0; // Prob de un 60% de que el camino sea libre
                else if (prob > 60 && prob <= 85) mapa[i][j] = 1;   // Prob de un 25% de que hayan bloques destructibles
                else mapa[i][j] = 2;    // Prob de un 15% de que hayan bloques indestructibles

            } 
        }
    }

    return mapa;
}


// Funcion para generar tanques 1 y 2 en posiciones validas del mapa
void generarTanques(int **mapa){
    int tanque1_x = 0, tanque1_y = 0;
    int tanque2_x = 0, tanque2_y = 0;

    // Ciclo para asignarle una posicion valida al tanque 1, apenas termine se le asignara la posicion
    do{
        tanque1_x = rand()%13;
        tanque1_y = rand()%13;
    } while (mapa[tanque1_x][tanque1_y] != 0);
    mapa[tanque1_x][tanque1_y] = 3;

    // Ciclo para asignarle una posicion valida al tanque 2, adicionalmente estara a una distancia minima de 5 unidades del otro tanque
    do{
        tanque2_x = rand()%13;
        tanque2_y = rand()%13;

    // Mientras la posicion sea invalida o la distancia sea menor que 6, el ciclo seguira
    } while (mapa[tanque2_x][tanque2_y] != 0 || sqrt(pow(tanque2_x - tanque1_x,2) + pow(tanque2_y - tanque1_y,2)) < 6);
    mapa[tanque2_x][tanque2_y] = 4;
}


// Funcion para realizar estudio de casillas libres, dejando marcas en todas las casillas que son accesibles ([0] y [1]) para detectar si quedaron zonas aisladas
void dfs(int x, int y, int **mapa, int **visitado, int filas, int columnas){

    // Marcamos casilla como visitada
    visitado[x][y] = 1;

    // Movimientos posibles para avanzar: derecha, izquierda, arriba, abajo
    int mov_x[4] = {1, -1, 0, 0};   
    int mov_y[4] = {0, 0, 1, -1};   

    // For con el que se exploran las 4 direcciones, lo principal de este es que si se encuentra una de las condiciones establecidas, no seguirá avanzando en esa dirección y pasará a otra
    // Si se visitan las 4 direcciones posibles ya sera el final del camino 
    for (int k = 0; k < 4; k++){

        // Casillas x,y que ira avanzando
        int av_x = x + mov_x[k];
        int av_y = y + mov_y[k];

        // Verificamos que este dentro del limite establecido (no deberia excederlo de todos modos pq matriz esta rodeada por casillas indestructibles)
        if (av_x < 0 || av_x >= filas || av_y < 0 || av_y >= columnas)
            continue;
        
        // Si ya fue visitada la celda, pasamos a la siguiente direccion
        if (visitado[av_x][av_y] == 1)
            continue;
        
        // Si es una celda indestructible, la ignora y pasa a la siguiente direccion posible
        if (mapa[av_x][av_y] == 2)
            continue;
        
        // Llamada recursiva para avanzar a siguiente celda en la direccion correspondiente
        dfs(av_x, av_y, mapa, visitado, filas, columnas);

    }

}


// Funcion para validacion del mapa leido/generado, definamos mapa valido como un mapa en el que los tanques no estan encerrados por bloques indestructibles
// Aunque dejamos la posibilidad (por temas de optimizacion) de que los tanques si puedan estar encerrados por bloques destructibles, este analisis lo hacemos mediante DFS
int validarMapa(int **mapa, int filas, int columnas){
    
    // Inicializamos matriz en memoria dinamica con la cual iremos marcando las celdas recorridas, en un principio estara llena de 0
    int **visitado = reservaMemoria(filas,columnas,1);

    // Hacemos un punto de inicio (x,y) que estarán marcados con -1, el cual significa que no está en una celda libre
    int x_inicial = -1, y_inicial = -1;

    // Exploraremos el mapa en busqueda de la primera celda sobre la cual nos podamos mover, recordar que los bordes del mapa son bloques indestructibles, por lo que los saltaremos
    for (int i = 1; i < filas - 1; i++){
        for (int j = 1; j < columnas - 1; j++){

            if (mapa[i][j] != 1 && mapa[i][j] != 2){    // Las unicas celdas no transitables son bloques destructibles (= 1) o indestructibles (= 2)
                x_inicial = i;
                y_inicial = j;
                break;
            }
        }
    }
    
    // Basta con que una coordenada no este en celda libre para concluir que no se encontraron celdas libres, se termina la funcion retornando False
    if (x_inicial == -1){
        liberaMemoria(visitado,filas);
        return 0;
    }

    // Hacemos trazado de los caminos posibles mediante funcion dfs
    dfs(x_inicial, y_inicial, mapa, visitado, filas, columnas);

    // Comprobaremos si todas las celdas que pueden ser transitables fueron marcadas mediante esta flag, si no es el caso, significa que hay uno o mas espacios aislados
    int valido = 1;

    for (int i = 1; i < filas - 1; i++){
        for (int j = 1; j < columnas - 1; j++){
            if ((mapa[i][j] != 1 && mapa[i][j] != 2) && visitado[i][j] == 0){   // Si es transitable pero no esta marcada, valido = False
                valido = 0;
                break;
            }
        }
    }

    liberaMemoria(visitado,filas);

    return valido;
    
}


// Funcion para generar mapa completamente valido, utilizando funciones de generarMapa (la cual no genera siempre uno valido), validarMapa(que estudia ese generado) y liberaMemoria
// La necesite porque repetia este proceso muchas veces en main ante el caso de que se recibiera un archivo invalido o querer generar un mapa desde 0
int **generarMapaValido(int filas, int columnas){
    int **mapa = generarMapa(filas,columnas);

    while (!validarMapa(mapa,filas,columnas)){
        liberaMemoria(mapa,filas);
        mapa = generarMapa(filas,columnas);
    }

    printf("Mapa aleatorio generado exitosamente!\n");

    generarTanques(mapa);
    return mapa;
}


// Funcion para almacenar el mapa en el archivo "mapa.txt" pasado por main
void almacenarMapa(int **mapa, int filas, int columnas, char *archivo){
    FILE *fmapa = fopen(archivo, "w");

    if (fmapa == NULL){
        printf("Error, no se pudo crear el archivo");
        return;
    }

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (j == columnas - 1) fprintf(fmapa,"%d\n",mapa[i][j]);
            else fprintf(fmapa,"%d ",mapa[i][j]);
        }
    }
}
