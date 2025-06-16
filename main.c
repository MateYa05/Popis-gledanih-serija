#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "serije.h"
#include "datoteka.h"

typedef enum {
    OPCIJA_DODAJ_SERIJU = 1,
    OPCIJA_PRETRAGA,
    OPCIJA_IZLAZ
} IzbornikOpcije;

int main() {
    int opcija;
    while (1) {
        printf("\n1. Dodaj seriju\n2. Pretraga\n3. Izlaz\nOdabir: ");
        scanf("%d", &opcija);

        if (opcija == 1) {
            Serija* s = unesiSeriju();
            if (s) {
                spremiSeriju(s);
                free(s->naziv);
                free(s);
                s->naziv = NULL;
                s = NULL;
            }
        }
        else if (opcija == 2) {
            int pod;
            printf("\n1. Po imenu\n2. Po zanru\nOdabir: ");
            scanf("%d", &pod);
            if (pod == 1) {
                char naziv[100];
                getchar();
                printf("Unesi naziv: ");
                fgets(naziv, sizeof(naziv), stdin);
                naziv[strcspn(naziv, "\n")] = 0;
                traziPoImenu(naziv);
            }
            else if (pod == 2) {
                Zanr z = unesiZanr();
                traziPoZanru(z);
            }
        }
        else if (opcija == 3) {
            break;
        }
        else {
            printf("Pogresan unos.\n");
        }
    }
    return 0;
}