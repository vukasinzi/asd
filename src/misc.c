#include <stdlib.h>
#include <time.h>
#include "misc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "datoteka.h"


void ocisti_ekran() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void datum(char out[7]) {
    time_t t = time(NULL);
    struct tm *tmv = localtime(&t);
    strftime(out, 7, "%y%m%d", tmv);

}

void kreiraj_foldere() {
#ifdef _WIN32
    _mkdir("..\\data");
    _mkdir("..\\data\\old");
    _mkdir("..\\rpt");
#else
    mkdir("../data", 0755);
    mkdir("../data/old", 0755);
    mkdir("../rpt", 0755);
#endif
}
void podesavanje() {
    kreiraj_foldere();
    char dat[7];
    datum(dat);
    podesi_pathove(dat);
}

