//
// Created by Thomas on 01/06/2020.
//

#include "stdlib.h"
#include "string.h"
#include "stdio.h"

typedef struct _element {
    char word[100];
    int count;
    struct _element *next;
} element;

typedef struct _list {
    element *head;
    element *tail;
} list;


element *createElement() {
    element *ptr = malloc(sizeof(element));

    strcpy(ptr->word, "");
    ptr->next = NULL;

    return ptr;
}

list *createList() {
    list *lst = malloc(sizeof(lst));

    element *el = createElement();
    lst->head = el;
    lst->tail = NULL;

    return lst;
}

void I_insert(list *lst, char *word) {
    element *elem = lst->head;
    while (elem->next != NULL) {
        elem = elem->next;
    }

    strcpy(elem->word, word);
    elem->next = createElement();
}


void I_delete(list *lst, char *word);

void I_print(list *lst) {
    element *current = lst->head;
    while (current) {
        printf("%s\n", current->word);
        current = current->next;
    }
}

element *I_find(list *lst, char *word);
