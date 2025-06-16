#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datoteka.h"
#include "serije.h"

void spremiSeriju(const Serija* s) {
    if (!s || !s->naziv) {
        printf("Neispravan podatak za spremanje.\n");
        return;
    }
    FILE* f = fopen(FILE_NAME, "a");
    if (!f) {
        perror("Greška otvaranja");
        return;
    }
    fprintf(f, "%s;%d;%d;%d;%.2f\n", s->naziv, s->zanr, s->brojSezona, s->brojEpizoda, s->ocjena);
    fclose(f);
}

void rekurzivnoCitaj(FILE* f, const char* trazenoIme, Zanr trazeniZanr, int poImenu) {
    char linija[256];
    if (!fgets(linija, sizeof(linija), f)) return;

    char naziv[100];
    int zanr, sez, epi;
    float ocjena;
    sscanf(linija, "%99[^;];%d;%d;%d;%f", naziv, &zanr, &sez, &epi, &ocjena);

    if ((poImenu && strcmp(naziv, trazenoIme) == 0) ||
        (!poImenu && zanr == trazeniZanr)) {
        printf("\nNaziv: %s\n", naziv);
        printf("Zanr: %s\n", zanr_nazivi[zanr]);
        printf("Sezone: %d\n", sez);
        printf("Epizode: %d\n", epi);
        printf("Ocjena: %.2f\n", ocjena);
    }

    rekurzivnoCitaj(f, trazenoIme, trazeniZanr, poImenu);
}

void traziPoImenu(const char* ime) {
    FILE* f = fopen(FILE_NAME, "r");
    if (!f) {
        perror("Datoteka nije dostupna");
        return;
    }
    rekurzivnoCitaj(f, ime, ZANR_UNKNOWN, 1);
    fclose(f);
}

void traziPoZanru(Zanr z) {
    FILE* f = fopen(FILE_NAME, "r");
    if (!f) {
        perror("Datoteka nije dostupna");
        return;
    }
    rekurzivnoCitaj(f, NULL, z, 0);
    fclose(f);
}