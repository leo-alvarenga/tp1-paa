//
// Created by caesar on 2/20/22.
//

#include "Interface.h"

void mainMenu()
{
    char filename[FILENAME_CHAR_MAX] = {"teste.txt"};
    int choice = 1;

    RelevantData data;

    int **log;
    int moves; moves = 0;

    map = NULL;

    while (true) {
        printf(" _______________________________________________________\n");
        printf("|                     MENU PRINCIPAL                    |\n");
        printf("|_______________________________________________________|\n");
        printf("| (?) Digite 0 em qualquer momento para sair            |\n");
        printf("| > Deseja ler o modelo de um arquivo?                  |\n");
        printf("|_______________________________________________________|\n");
        printf("> (1 - SIM; 2 - NÃO) >> ");
        scanf("%d", &choice);
        getc(stdin);

        if (choice <= 0)
            break;

        if (choice == 1) {
            printf("Insira o nome do arquivo:\n>> ");
            gets(filename);

            data = readFile(filename);
        } else {
            data = readFile(filename);
        }

        initMap(data.rows, data.cols, data.grid, data.enemies, data.hero);
        showMap();

        log = (int **)(malloc(sizeof(int *) * (data.rows * data.cols)));
        (*log) = (int *)(malloc(sizeof(int) * 2));

        int pos[2];
        pos[0] = map->startX; pos[1] = map->startY;
        move(pos, pos, map->ness->strength, map->ness->pkFlash);
    }


}
