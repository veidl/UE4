//
// Created by Thomas on 01/06/2020.
//

#ifndef UE4_LIST_H
#define UE4_LIST_H

typedef struct _element element;

typedef struct _list list;

element *createElement();

list *createList();

void I_insert(list *lst, char *word);

void I_delete(list *lst, char *word);

void I_print(list *lst);

element *I_find(list *lst, char *word);


#endif //UE4_LIST_H
