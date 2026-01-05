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

bool insert_u_datoteku(char* putanja, PROIZVOD* proizvod_);
bool insert_u_datoteku_tran(char* putanja, TRANSAKCIJA* transakcija);

bool ucitaj_sve(char* putanja,PROIZVOD** niz_p,int *i);
bool ucitaj_Id(char* putanja,unsigned id);
bool ucitaj_sve_tran(char* putanja,TRANSAKCIJA** niz_t,int *i);
bool ucitaj_Id_tran(char* putanja,unsigned id);

bool obrisi_Id(char* putanja,unsigned id);
void sortiraj_fajl(char* putanja,size_t velicina_sloga,Vrsta v);
void ocisti_bafer();

void update();
#endif