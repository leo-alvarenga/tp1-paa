//
// Created by caesar on 2/20/22.
//

#ifndef TP1_PAA_INPUT_H
#define TP1_PAA_INPUT_H

#include "../map/Map.h"

#define FILENAME_CHAR_MAX 50

typedef struct {
    int hero[2], enemies[5][2];

    int rows, cols;
    char **grid;
} RelevantData;

RelevantData readFile(char *filename);
bool charIsValid(char c);

#endif //TP1_PAA_INPUT_H
