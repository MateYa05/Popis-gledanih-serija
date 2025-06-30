#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serije.h"
#include "datoteka.h"

void spremiSeriju(const Serija* s) {
    if (!s || !s->naziv) {
        printf("Neispravan podatak za spremanje.\n");
        return;
    }
    FILE* f = fopen(FILE_NAME, "a");
    if (!f) {
        perror("Greska otvaranja");
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


int usporediPoOcjeni(const void* a, const void* b) {
    const Serija* sa = *(const Serija**)a;
    const Serija* sb = *(const Serija**)b;
    if (sa->ocjena > sb->ocjena) return -1;  
    if (sa->ocjena < sb->ocjena) return 1;
    return 0;
}

void traziPoZanru(Zanr z) {
    FILE* f = fopen(FILE_NAME, "r");
    if (!f) {
        perror("Datoteka nije dostupna");
        return;
    }

    Serija* serije[100];  
    int count = 0;

    char linija[256];
    while (fgets(linija, sizeof(linija), f)) {
        char naziv[100];
        int zanr, sez, epi;
        float ocjena;
        sscanf(linija, "%99[^;];%d;%d;%d;%f", naziv, &zanr, &sez, &epi, &ocjena);

        if (zanr == z) {
            Serija* novaSerija = malloc(sizeof(Serija));
            novaSerija->naziv = _strdup(naziv);
            novaSerija->zanr = zanr;
            novaSerija->brojSezona = sez;
            novaSerija->brojEpizoda = epi;
            novaSerija->ocjena = ocjena;
            serije[count++] = novaSerija;
        }
    }

   
    qsort(serije, count, sizeof(Serija*), usporediPoOcjeni);

   
    for (int i = 0; i < count; ++i) {
        printf("\nNaziv: %s\n", serije[i]->naziv);
        printf("Zanr: %s\n", zanr_nazivi[serije[i]->zanr]);
        printf("Sezone: %d\n", serije[i]->brojSezona);
        printf("Epizode: %d\n", serije[i]->brojEpizoda);
        printf("Ocjena: %.2f\n", serije[i]->ocjena);
        free(serije[i]->naziv);
        free(serije[i]);
    }

    fclose(f);
}

void obrisiSeriju(const char* ime) {
    FILE* f = fopen(FILE_NAME, "r");
    if (!f) {
        perror("Datoteka nije dostupna");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Greska prilikom stvaranja privremene datoteke");
        fclose(f);
        return;
    }

    char linija[256];
    int serijaObrisana = 0;

    while (fgets(linija, sizeof(linija), f)) {
        char naziv[100];
        sscanf(linija, "%99[^;];", naziv);
        if (strcmp(naziv, ime) != 0) {
            fputs(linija, tempFile);
        }
        else {
            serijaObrisana = 1;
        }
    }

    fclose(f);
    fclose(tempFile);

    if (serijaObrisana) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Serija '%s' je uspješno izbrisana.\n", ime);
    }
    else {
        remove("temp.txt");
        printf("Serija '%s' nije pronađena.\n", ime);
    }
}
