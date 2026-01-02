#ifndef DATOTEKA_H
#define DATOTEKA_H
#include <stdbool.h>
#include "defs.h"

#ifdef _WIN32
#define SEP "\\"
#else
#define SEP "/"
#endif


void podesi_pathove(const char* date);
bool kreiraj_datoteku(char* putanja);
bool unisti_datoteku(char* putanja);
bool insert_u_datoteku(char* putanja, PROIZVOD* proizvod);
bool ucitaj_sve(char* putanja);
bool ucitaj_Id(char* putanja,unsigned id);
bool obrisi_Id(char* putanja,unsigned id);

void ocisti_bafer();
#endif