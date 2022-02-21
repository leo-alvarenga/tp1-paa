//
// Created by caesar on 2/20/22.
//

#include "List.h"

void initList(List **list)
{
    list = (List **)(malloc(sizeof(List *)));
    *list = (List *)(malloc(sizeof(List)));

    (*list)->first =  (*list)->last = NULL;
    (*list)->length = 0;
}


void newNode(List **list, int x, int y, char symbol, int str, int pk)
{
    Node *aux;

    (*list)->last->next = (Node *)(malloc(sizeof(Node)));

    (*list)->last->next->prev = (*list)->last;
    aux = (*list)->last->next;

    (*list)->last = aux;

    (*list)->last->next = NULL;
    (*list)->last->x = x;
    (*list)->last->y = y;
    (*list)->last->symbol = symbol;
    (*list)->last->index = (*list)->length;
    (*list)->last->battleResult[0] = str;
    (*list)->last->battleResult[1] = pk;

    ++(*list)->length;
}


Node popNode(List **list)
{
    Node node, *aux;

    node.x = (*list)->last->x;
    node.y = (*list)->last->y;

    node.battleResult[0] = (*list)->last->battleResult[0];
    node.battleResult[1] = (*list)->last->battleResult[1];

    node.symbol = (*list)->last->symbol;

    aux = (*list)->last;
    (*list)->last = (*list)->last->prev;

    free(aux);
    --(*list)->length;

    return node;
}
