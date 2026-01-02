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

void ocisti_bafer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

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
    if (remove(putanja)==0) {
        kreiraj_datoteku(putanja);
        return true;
    }return false;
}

bool insert_u_datoteku(char* putanja, PROIZVOD* proizvod) {
    if (!postoji(putanja))
        kreiraj_datoteku(putanja);

    FILE *fajl = fopen(putanja, "rb");
    PROIZVOD p;

    while (fread(&p, sizeof(p), 1, fajl)==1) {
        if (p.Id == proizvod->Id) {
            return false;
        }
    }

    //pisanje
    fclose(fajl);
    fajl = fopen(putanja, "ab");
    if (fajl == NULL || fwrite(proizvod, sizeof(*proizvod), 1, fajl) != 1) {
        fclose(fajl);
        return false;
    }
    fclose(fajl);
    sortiraj_fajl(putanja);
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

bool obrisi_Id(char* putanja,unsigned id) {
    if (!postoji(putanja))
        return false;
    FILE * fajl = fopen(putanja,"rb");
    if (!fajl) return false;
    if (fseek(fajl,0,SEEK_END)!= 0) {fclose(fajl);return false;}
    long velicina_fajla = ftell(fajl);
    if (velicina_fajla < 0) return false;
    rewind(fajl);
    PROIZVOD p;
    PROIZVOD *niz_p = malloc((velicina_fajla/sizeof(PROIZVOD))*sizeof(*niz_p));

    int i = 0;
    bool flag = false;
    while (fread(&p,sizeof(p),1,fajl)) {
        if (p.Id == id) {
            flag = true;
            continue;
        }(niz_p)[i++]=p;
    }
    fclose(fajl);
    fajl = fopen(putanja,"wb");
    for (int j = 0;j < i;j++) {
        fwrite(&niz_p[j],sizeof(*niz_p),1,fajl);
    }
    fclose(fajl);
    free(niz_p);
    sortiraj_fajl(putanja);
    return flag;
}
void sortiraj_fajl(char* putanja) {
    if (!postoji(putanja))
        return;
    FILE * fajl = fopen(putanja,"rb");
    if (!fajl) return;
    if (fseek(fajl,0,SEEK_END)!= 0) {fclose(fajl);return ;}
    long velicina_fajla = ftell(fajl);
    if (velicina_fajla < 0) return;
    rewind(fajl);
    PROIZVOD p;
    PROIZVOD *niz_p = malloc((velicina_fajla/sizeof(PROIZVOD))*sizeof(*niz_p));
    int i = 0;
    while (fread(&p,sizeof(p),1,fajl)) {
      niz_p[i++]=p;
    }
    fclose(fajl);

    for (int x = 0;x < i;x++) {
        for (int y = 0;y<i;y++) {
            if (niz_p[x].Id != niz_p[y].Id && niz_p[x].Id < niz_p[y].Id) {
                PROIZVOD privremeni = niz_p[x];
                niz_p[x] = niz_p[y];
                niz_p[y] = privremeni;
            }
        }
    }
    fajl = fopen(putanja,"wb");
    for (int j = 0;j < i;j++) {
        fwrite(&niz_p[j],sizeof(*niz_p),1,fajl);
    }
    fclose(fajl);
    free(niz_p);


}
