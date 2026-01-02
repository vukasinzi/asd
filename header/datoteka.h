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
bool insert_u_datoteku_tran(char* putanja, TRANSAKCIJA* transakcija);

bool ucitaj_sve(char* putanja);
bool ucitaj_Id(char* putanja,unsigned id);
bool ucitaj_sve_tran(char* putanja);
bool ucitaj_Id_tran(char* putanja,unsigned id);

bool obrisi_Id(char* putanja,unsigned id);
void sortiraj_fajl(char* putanja);
void ocisti_bafer();
#endif