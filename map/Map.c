//
// Created by caesar on 2/20/22.
//

#include "Map.h"

char** initGrid(int rows, int cols)
{
    int i;
    char **grid = NULL;

    grid = (char **)(malloc(sizeof(char *) * rows));

    if (grid == NULL) {
        printf("Erro ao inicializar o grid do mapa. Por favor, inicie o programa novamente.\n\n");
        exit(1);
    }

    for (i = 0; i < rows; ++i) {
        grid[i] = (char *)(malloc(sizeof(char) * cols));

        if (grid[i] == NULL) {
            printf("Erro ao inicializar o grid do mapa. Por favor, inicie o programa novamente.\n\n");
            exit(1);
        }
    }

    return grid;
}


bool isPositionOccupied(int row, int col, int x, int y)
{
    if (x == row || y == col)
        return true;

    return false;
}

void initMap(int rows, int cols, char **grid, int enemies[5][2], int hero[2])
{
    int i, j;
    bool found;
    found = false;

    map = (Map *)(malloc(sizeof(Map)));

    if (map == NULL) {
        printf("Erro na alocação do Mapa. Por favor, inicie o programa novamente.\n\n");
        exit(1);
    }

    map->ness = initHero(hero[0], hero[1]);

    map->U = initEnemy(LIL_UFO, enemies[0][0], enemies[0][1]);
    map->T = initEnemy(TERRITORIAL_OAK, enemies[1][0], enemies[1][1]);
    map->S = initEnemy(STARMAN_JR, enemies[2][0], enemies[2][1]);
    map->B = initEnemy(MASTER_BELCH, enemies[3][0], enemies[3][1]);
    map->G = initEnemy(GIYGAS, enemies[4][0], enemies[4][1]);

    map->rows = rows;
    map->cols = cols;

    map->grid = grid;
    initList(&map->list);

    for (i = 0; i < map->rows; ++i) {

        if (found)
            break;

        for (j = 0; j < map->cols; ++j) {

            if (map->grid[i][j] == '@') {
                map->startX = i;
                map->startY = j;
                found = true;
            }

        }

    }

}


short tileType(int x, int y)
{
    if ((x < 0 || x >= map->rows) || (y < 0 || y >= map->cols))
        return INVALID;

    switch (map->grid[x][y]) {
        case '.':
            return INVALID;

        case '-':
            return HORIZONTAL;

        case '|':
            return VERTICAL;

        case '+':
            return CROSSING;

        case '@':
            return START;

        default:
            return ENEMY;
    }
}


bool isItTheLastMove(int oldX, int oldY, int newX, int newY)
{
    return (oldX == newX && oldY == newY);
}

/*
int* getEnemyStats(int x, int y) {
    int *res;

    res = (int *)(malloc(sizeof(int) * 2));

    switch (map->grid[x][y]) {
        case LIL_UFO:
            res[0] = map->U->strength;
            res[1] = map->U->reward;
            break;

        case TERRITORIAL_OAK:
            res[0] = map->T->strength;
            res[1] = map->T->reward;
            break;

        case STARMAN_JR:
            res[0] = map->S->strength;
            res[1] = map->S->reward;
            break;

        case MASTER_BELCH:
            res[0] = map->B->strength;
            res[1] = map->B->reward;
            break;

        default:
            res[0] = map->G->strength;
            res[1] = map->G->reward;
            break;
    }

    return res;
}
*/


bool move(int *oldPos, int *currentPos, int str, int pk)
{
    bool res[4][2]; // 0 cima 1 dir 2 baixo 3 esq
    int x, y;
    int next[2];
    x = currentPos[0]; y = currentPos[1];

    printf("%d %d: %c STR %d PK %d\n", x, y, map->grid[x][y], str, pk);

    if (tileType(x, y) == HORIZONTAL) {
        res[0][0] = res[0][1] = false;
        res[2][0] = res[2][1] = false;

        next[0] = x + 1; next[1] = y;
        res[1][0] = tileType(x + 1, y);
        if (res[1][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
            res[1][1] = move(currentPos, next, str, pk);
        }

        next[0] = x - 1; next[1] = y;
        res[3][0] = tileType(x - 1, y);
        if (res[3][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
            res[3][1] = move(currentPos, next, str, pk);
        }

        return (res[1][1] || res[3][1]);
    } else if (tileType(x, y) == VERTICAL) {
        res[1][0] = res[1][1] = false;
        res[3][0] = res[3][1] = false;

        next[0] = x; next[1] = y - 1;
        res[0][0] = tileType(x, y - 1);
        if (res[0][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
            res[0][1] = move(currentPos, next, str, pk);
        }

        next[0] = x; next[1] = y + 1;
        res[2][0] = tileType(x, y + 1);
        if (res[2][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
            res[2][1] = move(currentPos, next, str, pk);
        }

        return (res[0][1] || res[2][1]);
    } else if (tileType(x, y) == ENEMY) {
        int en[2];
        char enemy = map->grid[x][y];

        switch (enemy) {
            case LIL_UFO:
                en[0] = map->U->strength;
                en[1] = map->U->reward;
                break;

            case TERRITORIAL_OAK:
                en[0] = map->T->strength;
                en[1] = map->T->reward;
                break;

            case STARMAN_JR:
                en[0] = map->S->strength;
                en[1] = map->S->reward;
                break;

            case MASTER_BELCH:
                en[0] = map->B->strength;
                en[1] = map->B->reward;
                break;

            default:
                en[0] = map->G->strength;
                en[1] = map->G->reward;
                break;
        }

        if (en[0] <= str) {
            if (enemy == GIYGAS)
                return true;

            str += en[1];
        } else if (pk > 0 && enemy != GIYGAS) {
            pk -= 1;
        } else {
            return false;
        }

    }

    // up
    next[0] = x; next[1] = y - 1;
    res[0][0] = tileType(x, y - 1);
    if (res[0][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
        res[0][1] = move(currentPos, next, str, pk);
    }

    // right
    next[0] = x + 1; next[1] = y;
    res[1][0] = tileType(x + 1, y);
    if (res[1][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
        res[1][1] = move(currentPos, next, str, pk);
    }

    // down
    next[0] = x; next[1] = y + 1;
    res[2][0] = tileType(x, y + 1);
    if (res[2][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
        res[2][1] = move(currentPos, next, str, pk);
    }

    // left
    next[0] = x - 1; next[1] = y;
    res[3][0] = tileType(x - 1, y);
    if (res[3][0] && !isItTheLastMove(oldPos[0], oldPos[1], next[0], next[1])) {
        res[3][1] = move(currentPos, next, str, pk);
    }

    return (res[0][1] || res[1][1] || res[2][1] || res[3][1]);

}


void showMap()
{
    int i;

    printf("\n\n");

    for (i = 0; i < map->rows; ++i) {
        printf("%s\n", map->grid[i]);
    }
}