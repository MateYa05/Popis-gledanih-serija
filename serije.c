#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serije.h"

const char* zanr_nazivi[] = {
    "Drama", "Komedija", "Akcija", "Animacija", "Triler",
    "Horor", "Fantazija", "Dokumentarac", "Kriminalistika", "Romantika"
};

Zanr unesiZanr() {
    int odabir;
    printf("Odaberi zanr:\n");
    for (int i = 0; i <= ZANR_ROMANTIKA; ++i)
        printf("%d. %s\n", i + 1, zanr_nazivi[i]);

    printf("Unos: ");
    if (scanf("%d", &odabir) != 1 || odabir < 1 || odabir > ZANR_ROMANTIKA + 1) {
        printf("Neispravan unos. Postavlja se na 'Nepoznat'.\n");
        return ZANR_UNKNOWN;
    }
    return (Zanr)(odabir - 1);
}

Serija* unesiSeriju() {
    Serija* nova = malloc(sizeof(Serija));
    if (!nova) return NULL;

    char buffer[100];
    getchar();
    printf("Unesi naziv: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    nova->naziv = malloc(strlen(buffer) + 1);
    strcpy(nova->naziv, buffer);
    nova->zanr = unesiZanr();

    printf("Broj sezona: "); scanf("%d", &nova->brojSezona);
    printf("Broj epizoda: "); scanf("%d", &nova->brojEpizoda);
    printf("Ocjena: "); scanf("%f", &nova->ocjena);

    return nova;
}

void ispisiSeriju(const Serija* s) {
    printf("\nNaziv: %s\n", s->naziv);
    printf("Zanr: %s\n", zanr_nazivi[s->zanr]);
    printf("Sezone: %d\n", s->brojSezona);
    printf("Epizode: %d\n", s->brojEpizoda);
    printf("Ocjena: %.2f\n", s->ocjena);
}
