//
// Created by caesar on 2/20/22.
//

#ifndef TP1_PAA_ACTORS_H
#define TP1_PAA_ACTORS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define LIL_UFO           'U'
#define TERRITORIAL_OAK   'T'
#define STARMAN_JR        'S'
#define MASTER_BELCH      'B'
#define GIYGAS            'G'
#define NESS              '@'


typedef struct {
    char symbol;

    int strength;
    int reward;
} Enemy;

typedef struct {

    int strength;
    int pkFlash;
} Hero;

Hero* initHero(int strength, int pkFlash);
Enemy* initEnemy(char symbol, int strength, int reward);
int battleResult(Hero ness, Enemy enemy);

#endif //TP1_PAA_ACTORS_H
