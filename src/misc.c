#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "misc.h"

#include <ctype.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "datoteka.h"
#include <string.h>

#include "util.h"

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
    strftime(out, 7, "%d%m%y", tmv);
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
int poredi_tran(const void *a,const void *b) {
   TRANSAKCIJA* t1 = a;
    TRANSAKCIJA* t2 = b;
    if (t1->Id > t2->Id) return 1;
    return -1;
}
int poredi_proiz(const void *a,const void *b) {
    PROIZVOD *p1 = a;
    PROIZVOD *p2 = b;
    if (p1->Id > p2->Id) return 1;
    return -1;
}
int parsiraj_argumente(int argc,char* argv[]) {
    char arg[4];
    if (argc <= 1)
        return INT_MAX;
    strlcpy(arg, argv[1], sizeof(arg));
    if (arg[0]== '-' && arg[1] == 'd' && isdigit(arg[2])) {
        int a = atoi(&arg[2]);
        if (a >=1 && a <=5)
            return a;
    }
    return INT_MAX;
    //printf("%s\n",arg);
}
void podesi_meni(const int arg) {
        kopiraj_datoteku("../demo/demo_maticna.dat",mat_dat);
    switch (arg) {
        case 1:
            kopiraj_datoteku("../demo/demo_tran1.dat",tran_dat);
            break;
        case 2:
            kopiraj_datoteku("../demo/demo_tran2.dat",tran_dat);
            break;
        case 3:
            kopiraj_datoteku("../demo/demo_tran3.dat",tran_dat);
            break;
        case 4:
            kopiraj_datoteku("../demo/demo_tran4.dat",tran_dat);
            break;
        case 5:
            kopiraj_datoteku("../demo/demo_tran5.dat",tran_dat);
            break;
        default:
            break;
    }
}
