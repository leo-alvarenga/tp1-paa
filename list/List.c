//
// Created by caesar on 2/20/22.
//

#include "List.h"

List *initList()
{
    List *list;

    list = (List *)(malloc(sizeof(List)));

    list->last = list->first = NULL;
    list->length = 0;

    return list;
}


List *newNode(List *list, int x, int y, char symbol, int str, int pk)
{
    Node *aux;

    if (list == NULL)
        list = initList();

    if (list->last == NULL) {
        list->last = (Node *)(malloc(sizeof(Node)));

        list->last->next = NULL;
        list->last->x = x;
        list->last->y = y;
        list->last->symbol = symbol;
        list->last->index = list->length;
        list->last->battleResult[0] = str;
        list->last->battleResult[1] = pk;

        ++list->length;
        return list;
    }

    list->last->next = NULL;
    list->last->next = (struct node*)(malloc(sizeof (Node)));;

    list->last->next->prev = list->last;
    aux = list->last->next;

    list->last = aux;

    list->last->next = NULL;
    list->last->x = x;
    list->last->y = y;
    list->last->symbol = symbol;
    list->last->index = list->length;
    list->last->battleResult[0] = str;
    list->last->battleResult[1] = pk;

    ++list->length;

    return list;
}


List *popNode(List *list)
{
    Node *aux;
    aux = list->last;
    list->last = list->last->prev;

    free(aux);
    --list->length;

    return list;
}

void show(List *list)
{
    if (list != NULL) {
        int cont = list->length;
        Node *aux;
        aux = list->first;

        while (cont > 0) {
            aux = aux->next;

            if (aux == NULL)
                break;

            printf("Linha: %d, Coluna: %d", aux->x, aux->y);

            if (aux->battleResult[0] >= 0) {
                printf("; P: %d, K: %d", aux->battleResult[0], aux->battleResult[1]);
            }

            printf("\n");

            --cont;
        }
    }
}
