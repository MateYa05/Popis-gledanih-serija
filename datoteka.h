#ifndef DATOTEKA_H
#define DATOTEKA_H

#include "serije.h"

#define FILE_NAME "serije.txt"

void spremiSeriju(const Serija* s);
void traziPoImenu(const char* ime);
void traziPoZanru(Zanr z);

#endif
