/*#include <stdio.h>
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


}*/

//
//  main.c
//  ADAT Projekt Listen
//
//  Created by Herbert Paulis on 12.05.20.
//  Copyright © 2020 Herbert Paulis. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"


/**
 * based on Herbert Paulis
 * @param lst
 */
void printLetterCount(list *lst) {
    int frequencies[26] = {0};
    int global_count = 0;

    element *current = lst->head;
    while (current != NULL) {
        for (char *h = current->word; *h != '\0'; h++) {
            global_count += current->count;
            frequencies[*h - 'a'] += current->count;
        }
        current = current->next;
    }

    for (int i = 0; i < 26; ++i) {
        printf("%c: %d\n", i + 'a', frequencies[i]);
    }
    printf("sum letters: %d\n", global_count);
}

/**
 * filter out words with a lower count then 100
 * @param lst
 */
void filterWordsLt100(list *lst) {
    element *current = lst->head;

    while (current) {
        // need temp 'cause element is going to be deleted
        element *tmpElement = current;
        current = tmpElement->next;
        if (tmpElement->count < 100) {
            I_delete(lst, tmpElement->word);
        }
    }
}


int main() {
    list *mainList = createList();

    FILE *datei;
    char zeile[300];        // sicher lang genug fuer eine Zeile

    datei = fopen("C:\\Users\\Thomas\\CLionProjects\\UE4\\alice.txt", "r");

    if (!datei) // bei Fehler wird NULL zurueckgegeben
    {
        printf("Fehler beim Oeffnen\n");
        return 1;
    }

    while (!feof(datei))    // Solange nicht Dateiende erreicht wurde
    {
        fgets(zeile, 300, datei);
        if (isspace(zeile[0]))  // Eliminieren von Leerzeilen
            continue;
        zeile[strcspn(zeile, "\r\n")] = 0; // ersetzt beliebeige Kombination von CR&LF durch 0

        // Alternative fuer die folgende while-schleife: C-Funktion strtok()
        // https://en.cppreference.com/w/c/string/byte/strtok

        int zeilen_index = 0;   // Positionszaehler in der Zeile
        while (zeilen_index < strlen(zeile)) {
            char wort[100];
            int wort_index = 0; // Positionszaehler im Wort
            int skip_extra = 0; // uebersprungene Zeichen

            for (int i = zeilen_index; i < strlen(zeile); i++) {
                if (zeile[i] == ' ')    // Leerzeichen
                {
                    if (i != zeilen_index)  // Wortende
                    {
                        break;
                    } else                    // Zusätzliches Leerzeichen am Wort-/Zeilenanfang
                    {
                        skip_extra++;       // Merken, muessen spaeter dazugezaehlt werden
                        continue;
                    }
                }
                if (!isalpha(zeile[i])) // ueberspringe alles, was kein Buchstabe ist
                {
                    skip_extra++;       // Merken, muessen spaeter dazugezaehlt werden
                    continue;
                }
                wort[wort_index] = tolower(zeile[i]);   // Groszbuchsteben in Kleinbuchstaben umwandeln
                wort_index++;
            }
            wort[wort_index] = 0;
            zeilen_index += wort_index + skip_extra + 1;    // Zeilenindex korrigieren

            /*******************************************************************************/
            // Hier ist das jeweilige Wort in Variable wort enthalten zur spaeteren Weiterverarbeitung in der Liste
            // Achtung: wort kann Leerstring "" enthalten (z.B. wenn Zahl im Text war)!

            element *e = I_find(mainList, wort);
            // only insert new word else up the counter of the word
            if (e == NULL) {
                I_insert(mainList, wort, mainList->count);
            } else {
                e->count++;
            }
            /*******************************************************************************/
        }
    }
    printf("BEFORE FILTERING\n");
    I_print(mainList);
    printLetterCount(mainList);

    printf("\nAFTER FILTERING\n");

    filterWordsLt100(mainList);

    printLetterCount(mainList);

    return 0;
}



