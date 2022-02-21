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


bool move(int *oldPos, int *currentPos, int str, int pk, List **list)
{
    bool res = false;
    int x, y, next[2];
    x = currentPos[0];
    y = currentPos[1];

    if (isItTheLastMove(oldPos[0], oldPos[1], currentPos[0], currentPos[1])) {
        return false;
    }

    if (tileType(x, y)) { // verifica se eh valido
        *list = newNode(*list, x, y, map->grid[x][y], str, pk);

        if (tileType(x, y) == CROSSING || tileType(x, y) == START) { // verifica se eh o inicio ou cruzamento
            if (tileType(x - 1, y)) { // verifica em cima
                next[0] = x - 1;
                next[1] = y;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x, y + 1)) { // verifica a direita
                next[0] = x;
                next[1] = y + 1;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x + 1, y)) { // verifica embaixo
                next[0] = x + 1;
                next[1] = y;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x, y - 1)) { // verifica a esq
                next[0] = x;
                next[1] = y - 1;

                res = move(currentPos, next, str, pk, list);
            }
        } else if (tileType(x, y) == HORIZONTAL) {
            if (tileType(x, y + 1)) {
                next[0] = x;
                next[1] = y + 1;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x, y - 1)) {
                next[0] = x;
                next[1] = y - 1;

                res = move(currentPos, next, str, pk, list);
            }
        } else if (tileType(x, y) == VERTICAL) {
            if (tileType(x - 1, y)) {
                next[0] = x - 1;
                next[1] = y;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x + 1, y)) {
                next[0] = x + 1;
                next[1] = y;

                res = move(currentPos, next, str, pk, list);
            }
        } else {
            int stats[2];

            switch (map->grid[x][y]) {
                case LIL_UFO:
                    stats[0] = map->U->strength;
                    stats[1] = map->U->reward;
                    break;

                case TERRITORIAL_OAK:
                    stats[0] = map->T->strength;
                    stats[1] = map->T->reward;
                    break;

                case STARMAN_JR:
                    stats[0] = map->S->strength;
                    stats[1] = map->S->reward;
                    break;

                case MASTER_BELCH:
                    stats[0] = map->B->strength;
                    stats[1] = map->B->reward;
                    break;

                default:
                    stats[0] = map->G->strength;
                    stats[1] = map->G->reward;
                    break;
            }

            if (stats[0] <= str) {
                if (map->grid[x][y] == GIYGAS)
                    return true;

                str += stats[1];
            } else if (pk > 0 && map->grid[x][y] != GIYGAS) {
                pk -= 1;
            } else {
                *list = popNode(*list);
                return false;
            }

            (*list)->last->battleResult[0] = str;
            (*list)->last->battleResult[1] = pk;

            if (tileType(x - 1, y)) {
                next[0] = x - 1;
                next[1] = y;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x, y + 1)) {
                next[0] = x;
                next[1] = y + 1;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x + 1, y)) {
                next[0] = x + 1;
                next[1] = y;

                res = move(currentPos, next, str, pk, list);
            }

            if (!res && tileType(x, y - 1)) {
                next[0] = x;
                next[1] = y - 1;

                res = move(currentPos, next, str, pk, list);
            }
        }
    }

    if (!res)
        *list = popNode(*list);

    return res;
}


void showMap()
{
    int i;

    printf("\n\n");

    for (i = 0; i < map->rows; ++i) {
        printf("%s\n", map->grid[i]);
    }
}