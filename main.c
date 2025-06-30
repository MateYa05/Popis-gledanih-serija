#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "serije.h"
#include "datoteka.h"
#include <string.h>

typedef enum {
    OPCIJA_DODAJ_SERIJU = 1,
    OPCIJA_PRETRAGA,
    OPCIJA_OBRISI_SERIJU,  
    OPCIJA_IZLAZ
} IzbornikOpcije;

int main() {
    int opcija;
    while (1) {
        printf("\n1. Dodaj seriju\n2. Pretraga\n3. Obrisi seriju\n4. Izlaz\nOdabir: ");
        scanf("%d", &opcija);

        if (opcija == OPCIJA_DODAJ_SERIJU) {
            Serija* s = unesiSeriju();
            if (s) {
                spremiSeriju(s);
                free(s->naziv);
                free(s);
            }
        }
        else if (opcija == OPCIJA_PRETRAGA) {
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
        else if (opcija == OPCIJA_OBRISI_SERIJU) {
            char naziv[100];
            getchar();  
            printf("Unesi naziv serije koju želiš obrisati: ");
            fgets(naziv, sizeof(naziv), stdin);
            naziv[strcspn(naziv, "\n")] = 0;
            obrisiSeriju(naziv);
        }
        else if (opcija == OPCIJA_IZLAZ) {
            break;
        }
        else {
            printf("Pogresan unos.\n");
        }
    }
    return 0;
}
