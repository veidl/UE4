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
//        printf("%s\n", zeile);  // Testausgabe

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
            if (wort_index != NULL) {
                element *e = I_find(mainList, wort);

                if (e == NULL) {
                    I_insert(mainList, wort, mainList->count);
                } else {
                    e->count++;
                }

            }
//            printf("%s:", wort);    // Testausgabe
            /*******************************************************************************/
        }
//        printf("\n");   // Nur fuer Testausgabe
    }
//    I_print(mainList);
//    I_print_letter_count(mainList);

    printf("\n");

    getOnlySome(mainList);
//    I_print(mainList);
//    I_print_letter_count(mainList);


    return 0;
}

void I_print_letter_count(list *lst) {
    int frequencies[26] = {0};

    element *current = lst->head;
    while (current) {
        for (char *h = current->word; *h != '\0'; h++) {
            frequencies[*h - 'a'] += current->count;
        }
        current = current->next;
    }

    for (int i = 0; i < 26; ++i) {
        printf("%c: %d\n", i + 'a', frequencies[i]);
    }
}

void getOnlySome(list *lst) {
    element *current = lst->head;

    // TODO fix that -> cant delete next element (prob the freeing of memory is the issue)
    while (current) {
        element *tmpElement = current;
//        int tmp = current->count;

        if (current->count < 100) {
            I_delete(lst, current->word);
        }
        current = tmpElement->next;
    }
}


