//
// Created by Thomas, Sahil, Oliver on 01/06/2020.
//

#ifndef UE4_LIST_H
#define UE4_LIST_H

typedef struct _element {
    char word[100];
    int count;
    struct _element *next;
} element;

typedef struct _list {
    element *head;
    int count;
} list;


list *createList();

void I_insert(list *lst, char *word, int index);

void I_delete(list *lst, char *word);

void I_print(list *lst);

element *I_find(list *lst, char *word);

#endif //UE4_LIST_H
