//
// Created by Thomas on 01/06/2020.
//


#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "list.h"


list *createList() {
    list *lst = malloc(sizeof(list));
    lst->head = NULL;
    lst->count = 0;
    return lst;
}

void I_insert(list *lst, char *word, int index) {

    element *newElement;
    element *tmpElement;

    newElement = malloc(sizeof(element));
    strcpy(newElement->word, word);

    if (lst->head == NULL) {
        newElement->next = NULL;
        lst->head = newElement;
        lst->count = 1;
        return;
    }

    tmpElement = lst->head;
    for (int i = 0; i < index - 1; i++) {
        tmpElement = tmpElement->next;
    }

    newElement->next = tmpElement->next;
    tmpElement->next = newElement;
    lst->count += 1;
}


void I_delete(list *lst, char *word) {

    element *current = lst->head;

    if (strcmp(current->word, word) == 0) {
        lst->head = current->next;
        free(current);
        lst->count--;
        return;
    }

    while (current) {
        if (strcmp(current->next->word, word) == 0) {
            list *tmp = (list *) current->next;
            current->next = current->next->next;
            free(tmp);
            lst->count--;
            return;
        }
        current = current->next;
    }
}

void I_print(list *lst) {
    element *current = lst->head;
    while (current) {
        printf("%s\n", current->word);
        current = current->next;
    }
}

element *I_find(list *lst, char *word) {

    element *current = lst->head;

    while (current) {
        if (strcmp(current->word, word) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;

}
