#include <stdio.h>
#include "list.h"
#include "string.h"


int main() {

    char buffer[100];

    list *mainList = createList();

    strcpy(buffer, "test");

    I_insert(mainList, buffer, 0);

    strcpy(buffer, "HUGOFISCHKOPF");
    I_insert(mainList, buffer, 1);

    strcpy(buffer, "sahilp");
    I_insert(mainList, buffer, 2);

    strcpy(buffer, "oliver");
    I_insert(mainList, buffer, 3);

    I_print(mainList);

    I_delete(mainList, "sahilp");

    printf("\n");
    I_print(mainList);

    I_find(mainList, "oliver");

    return 0;
}
