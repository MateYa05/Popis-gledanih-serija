#ifndef SERIJA_H
#define SERIJA_H

typedef enum {
    ZANR_DRAMA, ZANR_KOMEDIJA, ZANR_AKCIJA, ZANR_ANIMACIJA, ZANR_TRILER,
    ZANR_HOROR, ZANR_FANTAZIJA, ZANR_DOKUMENTARAC, ZANR_KRIMINALISTIKA, ZANR_ROMANTIKA,
    ZANR_UNKNOWN
} Zanr;

extern const char* zanr_nazivi[];

typedef struct {
    char* naziv;
    Zanr zanr;
    int brojSezona;
    int brojEpizoda;
    float ocjena;
} Serija;

Zanr unesiZanr();
Serija* unesiSeriju();
void ispisiSeriju(const Serija* s);

#endif
