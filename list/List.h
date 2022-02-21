//
// Created by caesar on 2/20/22.
//

#ifndef TP1_PAA_LIST_H
#define TP1_PAA_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int index;
    int x, y;
    char symbol;
    int battleResult[2];
    struct node *next, *prev;
} Node;

typedef struct {
    int length;
    Node *first, *last;
} List;


List *initList();
List *newNode(List *list, int x, int y, char symbol, int str, int pk);
List *popNode(List *list);
void show(List *list);

#endif //TP1_PAA_LIST_H
