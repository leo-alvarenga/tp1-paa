//
// Created by caesar on 2/20/22.
//

#ifndef TP1_PAA_MAP_H
#define TP1_PAA_MAP_H


#define INVALID    0
#define HORIZONTAL 1
#define VERTICAL   2
#define CROSSING   3
#define ENEMY      4
#define START      5

#include "../entities/Actors.h"
#include "../list/List.h"


typedef struct {
    Enemy *U, *T, *S, *B, *G;
    Hero *ness;

    char **grid;
    int rows, cols;

    int startX, startY;
    List *list;
} Map;

Map *map;

void initMap(int rows, int cols, char **grid, int enemies[5][2], int hero[2]);
char** initGrid(int rows, int cols);

short tileType(int x, int y);
bool isItTheLastMove(int oldX, int oldY, int newX, int newY);
int* getEnemyStats(int x, int y);

bool move(int *oldPos, int *currentPos, int str, int pk);

bool isPositionOccupied(int row, int col, int x, int y);
void showMap();

#endif //TP1_PAA_MAP_H
