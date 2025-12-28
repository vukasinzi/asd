#include <stdbool.h>
#ifndef DATOTEKA_H
#define DATOTEKA_H

#ifdef _WIN32
#define SEP "\\"
#else
#define SEP "/"
#endif


void podesi_pathove(const char* date);
bool kreiraj_datoteku(char* putanja);

#endif