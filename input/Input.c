//
// Created by caesar on 2/20/22.
//

#include "Input.h"

bool charIsValid(char c)
{
    if (c != LIL_UFO && c != TERRITORIAL_OAK && c != STARMAN_JR && c != MASTER_BELCH) {
        if (c != GIYGAS && c != NESS && c != '-' && c != '+' && c != '|' && c != '.')
            return false;
    }

    return true;
}


RelevantData readFile(char *filename)
{
    int line, currentLine;
    line = 0;

    char *out;
    out = NULL;

    FILE *fp;
    fp = fopen(filename, "r");

    RelevantData data;

    if (fp == NULL) {
        printf("Arquivo \'%s\' não encontrado. Por favor, inicie o programa novamente.", filename);
        exit(1);
    }

    while (!feof(fp)) {
        if (line > 7) {

            if (out != NULL) {
                fgets(out,data.cols, fp);
                getc(fp);

                for (int i = 0; i < data.cols; ++i) {
                    data.grid[currentLine][i] = out[i];
                }

                ++currentLine;
            }

        } else {

            switch (line) {

                case 0:
                    fscanf(fp, "%d %d", &data.hero[0], &data.hero[1]);
                    break;

                case 1:
                    fscanf(fp, "%d %d", &data.enemies[0][0], &data.enemies[0][1]);
                    break;

                case 2:
                    fscanf(fp, "%d %d", &data.enemies[1][0], &data.enemies[1][1]);
                    break;

                case 3:
                    fscanf(fp, "%d %d", &data.enemies[2][0], &data.enemies[2][1]);
                    break;

                case 4:
                    fscanf(fp, "%d %d", &data.enemies[3][0], &data.enemies[3][1]);
                    break;
                case 5:
                    fscanf(fp, "%d %d", &data.enemies[4][0], &data.enemies[4][1]);
                    break;

                default:
                    fscanf(fp, "%d %d", &data.rows, &data.cols);

                    out = (char *)(malloc(sizeof(char) * (data.cols)));

                    char grid[data.rows][data.cols];

                    data.grid = initGrid(data.rows, data.cols);

                    currentLine = 0;

                    break;

            }

        }

        ++line;

    }

    return data;

}
