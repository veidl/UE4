//
// Created by Thomas, Sahil, Oliver on 01/06/2020.
//


#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "list.h"


/**
 * initialize list with malloc
 * only used when creating a new list
 * @return new list
 */
list *createList() {
    list *lst = malloc(sizeof(list));
    lst->head = NULL;
    lst->count = 0;
    return lst;
}

/**
 * allows you to insert a word in any place of the list
 * @param lst list
 * @param word new word to insert
 * @param index where to insert
 */

void I_insert(list *lst, char *word, int index) {
    // check if word is actually a word
    if (strcmp(word, "") == 0 && word != NULL) {
        return;
    }

    element *newElement;
    element *tmpElement;

    // create new element with the size of one element (doesnt matter how long the word is)
    newElement = malloc(sizeof(element));
    strcpy(newElement->word, word);
    // set the count of the word to 1
    newElement->count = 1;

    // check if the head is null, if -> our new element is now the head
    if (lst->head == NULL) {
        // new element is the last element so next pointer is null
        newElement->next = NULL;
        lst->head = newElement;
        lst->count = 1;
        return;
    }

    // if list was not empty
    tmpElement = lst->head;
    for (int i = 0; i < index - 1; i++) {
        // go to the element on the index from parameter
        tmpElement = tmpElement->next;
    }
    // new elements next points to the indexed's next
    newElement->next = tmpElement->next;

    // place new element in position of index
    tmpElement->next = newElement;
    lst->count += 1;
}

/**
 * Deletes the first element with a certain criteria (word)
 * @param lst List
 * @param word Word to delete
 */
void I_delete(list *lst, char *word) {
    element *current = lst->head;

    // Check if Head Element to delete -> Set new Header to second element
    if (strcmp(current->word, word) == 0) {
        lst->head = current->next;
        free(current);
        lst->count--;
        return;
    }

    // Go through every element and check if word to delete is contained
    while (current) {
        if (strcmp(current->next->word, word) == 0) {
            // Save to delete element in tmp
            list *to_delete = (list *) current->next;
            // The previous element (before the to-delete-element) needs to show to the to-delete's next element
            current->next = current->next->next;
            // Free the memory (otherwise memory leak)
            free(to_delete);
            // Decrement list count
            lst->count--;
            return;
        }
        current = current->next;
    }
}

/**
 * print list with their associated word count
 * @param lst
 */
void I_print(list *lst) {

    int global_count = 0;

    element *current = lst->head;
    while (current) {
        global_count += current->count;
        printf("%s: %d\n", current->word, current->count);
        current = current->next;
    }
    printf("\n");
    printf("global words: %d\n", global_count);
}

/**
 * Find word in list
 * @param lst
 * @param word
 * @return if_found ? word : null
 */
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
