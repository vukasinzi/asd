#include  <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "datoteka.h"
#include <ctype.h>
#include <defs.h>
#include <string.h>
char mat_dat[256];
char tran_dat[256];
char mat_tek[256];
char tran_tek[256];
char mat_nova[256];
char prom_rpt[256];
char err_kol_rpt[256];
char nov_pro_rpt[256];
char err_pro_rpt[256];


void podesi_pathove(const char *date) {
    snprintf(mat_dat, sizeof mat_dat, "..%sasd%sdata%smaticna.dat", SEP, SEP, SEP);
    snprintf(tran_dat, sizeof tran_dat, "..%sasd%sdata%stransakciona.dat", SEP, SEP, SEP);
    snprintf(mat_tek, sizeof mat_tek, ".%sasd%sdata%sold%smat_%s.dat", SEP, SEP, SEP, SEP, date);
    snprintf(tran_tek, sizeof tran_tek, ".%sasd%sdata%sold%stran_%s.dat", SEP, SEP, SEP, SEP, date);
    snprintf(mat_nova, sizeof mat_nova, ".%sasd%sdata%smaticna.dat", SEP, SEP, SEP);
    snprintf(prom_rpt, sizeof prom_rpt, ".%sasd%srpt%sprom_%s.rpt", SEP, SEP, SEP, date);
    snprintf(err_kol_rpt, sizeof err_kol_rpt, ".%sasd%srpt%serr_kol_%s.rpt", SEP, SEP, SEP, date);
    snprintf(nov_pro_rpt, sizeof nov_pro_rpt, ".%sasd%srpt%snov_pro_%s.rpt", SEP, SEP, SEP, date);
    snprintf(err_pro_rpt, sizeof err_pro_rpt, ".%sasd%srpt%serr_pro_%s.rpt", SEP, SEP, SEP, date);
}
bool postoji(char * putanja) {
    FILE* fajl = fopen(putanja,"rb");
    if (fajl == NULL)
        return false;
    fclose(fajl);
    return true;
}
bool kreiraj_datoteku(char* putanja) {
    if (postoji(putanja)) {
        char c;
        printf("Datoteka vec postoji, pregaziti je?(d/n)");
        if (scanf(" %c",&c)!=1) return false;
        while ((getchar()) != '\n'){}//ciscenje buffera
        if (tolower(c) !='d')return false;
    }
    FILE *fajl = fopen(putanja,"wb");
    if (fajl == NULL)
        return false;
    fclose(fajl);
    return true;
}
bool unisti_datoteku(char* putanja) {
    if (!postoji(putanja))
        return false;
    if (remove(putanja)==0)
        return true;
    return false;
}

bool insert_u_datoteku(char* putanja, PROIZVOD* proizvod) {
    if (!postoji(putanja))
        kreiraj_datoteku(putanja);
    unsigned poslednji_id = 0;
    FILE *fajl = fopen(putanja, "rb");
    PROIZVOD p;
    PROIZVOD poslednji;
    while (fread(&p, sizeof(p), 1, fajl)==1) {
        poslednji_id = p.Id;
    }
    poslednji_id++;
    (*proizvod).Id= poslednji_id;
    //pisanje
    fclose(fajl);
    fajl = fopen(putanja, "ab");
    if (fajl == NULL || fwrite(proizvod, sizeof(*proizvod), 1, fajl) != 1) {
        fclose(fajl);
        return false;
    }
    fclose(fajl);
    return true;
}
bool ucitaj_sve(char* putanja) {
    if (!postoji(putanja))
        return false;
    FILE* fajl = fopen(putanja, "rb");
    PROIZVOD p;
    bool flag = false;
   while (fread(&p,sizeof(p),1,fajl)) {
       flag = true;
       printf("Id:%u, Naziv: %s, Kolicina: %u\n",p.Id,p.Naziv,p.Kolicina);
   }
    fclose(fajl);
    return flag;
}
bool ucitaj_Id(char* putanja,unsigned id) {
    if (!postoji(putanja))
        return false;
    FILE * fajl = fopen(putanja,"rb");
    PROIZVOD p;
    bool flag = false;
    while (fread(&p, sizeof(p),1,fajl)) {
        if (p.Id == id) {
            flag = true;
            printf("Id:%u, Naziv: %s, Kolicina: %u\n",p.Id,p.Naziv,p.Kolicina);
        }
    }
    fclose(fajl);
    return flag;
}