//
// Created by caesar on 2/20/22.
//

#include "Actors.h"

Hero* initHero(int strength, int pkFlash)
{
    Hero *ness = NULL;
    ness = (Hero *)(malloc(sizeof(Hero)));

    if (ness == NULL) {
        printf("Erro na alocação do herói Ness. Por favor, inicie o programa novamente.\n\n");
        exit(1);
    }

    ness->strength = strength;
    ness->pkFlash = pkFlash;

    return ness;
}


Enemy* initEnemy(char symbol, int strength, int reward)
{
    Enemy *enemy = NULL;
    enemy = (Enemy *)(malloc(sizeof(Enemy)));

    if (enemy == NULL) {
        printf("Erro na alocação do inimigo \'%c\'. Por favor, inicie o programa novamente.\n\n", symbol);
        exit(1);
    }

    enemy->symbol = symbol;
    enemy->strength = strength;
    enemy->reward = reward;

    return enemy;
}


int battleResult(Hero ness, Enemy enemy)
{
    if (ness.strength >= enemy.strength) {
        return enemy.reward;
    }

    return 0;
}

