#include <stdio.h>
#include "list.h"


int main() {

    list *l = createList();

    char buffer[100];
    scanf("%s", buffer);

    I_insert(l, buffer);

    scanf("%s", buffer);
    I_insert(l, buffer);
    I_print(l);

    return 0;
}
