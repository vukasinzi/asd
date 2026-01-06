#include  <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "datoteka.h"
#include <ctype.h>
#include <defs.h>
#include <string.h>
#include <misc.h>
#include <util.h>
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
    snprintf(mat_dat, sizeof mat_dat, "..%sdata%smaticna.dat", SEP, SEP);
    snprintf(tran_dat, sizeof tran_dat, "..%sdata%stransakciona.dat", SEP, SEP);
    snprintf(mat_tek, sizeof mat_tek, "..%sdata%sold%smat_%s.dat", SEP, SEP, SEP, date);
    snprintf(tran_tek, sizeof tran_tek, "..%sdata%sold%stran_%s.dat", SEP, SEP, SEP, date);
    snprintf(mat_nova, sizeof mat_nova, "..%sdata%smaticna.dat", SEP, SEP);
    snprintf(prom_rpt, sizeof prom_rpt, "..%srpt%sprom_%s.rpt", SEP, SEP, date);
    snprintf(err_kol_rpt, sizeof err_kol_rpt, "..%srpt%serr_kol_%s.rpt", SEP, SEP, date);
    snprintf(nov_pro_rpt, sizeof nov_pro_rpt, "..%srpt%snov_pro_%s.rpt", SEP, SEP, date);
    snprintf(err_pro_rpt, sizeof err_pro_rpt, "..%srpt%serr_pro_%s.rpt", SEP, SEP, date);

}
bool postoji(char * putanja) {
    FILE* fajl = fopen(putanja,"rb");
    if (fajl == NULL)
        return false;
    fclose(fajl);
    return true;
}
bool kreiraj_izvestaj(char *putanja) {
    FILE *fajl = fopen(putanja,"a");
    if (fajl == NULL)
        return false;
    fclose(fajl);
    return true;
}
bool kreiraj_datoteku(char* putanja,bool flag) {
    if (postoji(putanja) && flag == false) {
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
        return true;
    }return false;
}
bool insert_u_izvestaj_proizvod(char* putanja,PROIZVOD* proizvod_) {
    FILE *fajl = fopen(putanja, "a");
    if (fajl == NULL || fprintf(fajl, "Id: %u, Naziv: %s, Kolicina: %u\n", proizvod_->Id, proizvod_->Naziv, proizvod_->Kolicina) != 1) {
        fclose(fajl);
        return false;
    }
    fclose(fajl);
    return true;
}
void insert_u_izvestaj_greska(char* putanja,PROIZVOD* p_,TRANSAKCIJA* t_,char greska[]) {
    FILE *fajl = fopen(putanja, "a");
    char *promena = (t_->Promena == ULAZ) ? "ULAZ" : "IZLAZ";
    if (strcmp(greska,"Nepostojeci proizvod") == 0) {
        if (fajl == NULL || fprintf(fajl, "Id: %u, Naziv: X, Kolicina: X, Tip: %s(-), Kolicina: %u, Greska: %s\n", t_->Id,promena,t_->Kolicina,greska) != 1) {
            fclose(fajl);

        }
    }
    else if (strcmp(greska,"Nepostojeca kolicina proizvoda") == 0) {
        if (fajl == NULL || fprintf(fajl, "Id: %u, Naziv: %s, Kolicina: %u, Tip:%s , Kolicina: %u, Greska: %s\n", p_->Id,p_->Naziv,p_->Kolicina,promena,t_->Kolicina,greska) != 1) {
            fclose(fajl);
        }
    }
}
bool insert_u_datoteku(char* putanja, PROIZVOD* proizvod_) {
    if (!postoji(putanja))
        kreiraj_datoteku(putanja,false);

    FILE *fajl = fopen(putanja, "rb");
    PROIZVOD p;

    while (fread(&p, sizeof(p), 1, fajl)==1) {
        if (p.Id == proizvod_->Id) {
            return false;
        }
    }

    //pisanje
    fclose(fajl);
    fajl = fopen(putanja, "ab");
    if (fajl == NULL || fwrite(proizvod_, sizeof(*proizvod_), 1, fajl) != 1) {
        fclose(fajl);
        return false;
    }
    fclose(fajl);
    sortiraj_fajl(putanja,sizeof(PROIZVOD),proizvod);

    return true;
}
bool insert_u_datoteku_tran(char* putanja, TRANSAKCIJA* transakcija) {
    if (!postoji(putanja))
        kreiraj_datoteku(putanja,false);
    FILE *fajl = fopen(putanja, "ab");
    if (fajl == NULL || fwrite(transakcija, sizeof(TRANSAKCIJA), 1, fajl) != 1) {
        fclose(fajl);
        return false;
    }
    fclose(fajl);
    return true;
}
int broj_elemenata_(char* putanja,Vrsta v) {
    FILE* fajl = fopen(putanja,"rb");
    int i = 0;

    if (v == proizvod) {
        PROIZVOD p;
        while (fread(&p,sizeof(p),1,fajl)) {
                i++;
        }
    }
    else if (v == transakcija) {
        TRANSAKCIJA t;
        while (fread(&t,sizeof(t),1,fajl)) {
            i++;
        }
    }
    fclose(fajl);
    return i;
}
bool ucitaj_sve(char* putanja,PROIZVOD** niz_p,int *i) {
    if (!postoji(putanja))
        return false;
    FILE* fajl = fopen(putanja, "rb");
    PROIZVOD p;
    bool flag = false;

    int kapacitet = 16;
    PROIZVOD *niz = malloc(kapacitet*sizeof(PROIZVOD));
    if (niz_p == NULL)
        free(niz);
    while (fread(&p,sizeof(p),1,fajl)) {
        flag = true;
        if (niz_p == NULL) {
           printf("Id:%u, Naziv: %s, Kolicina: %u\n",p.Id,p.Naziv,p.Kolicina);
           continue;
        }
        if (*i >= kapacitet) {
            kapacitet *= 2;
            PROIZVOD *tmp = realloc(niz, kapacitet * sizeof(PROIZVOD));
            niz = tmp;
        }
        niz[(*i)++] = p;

    }
    fclose(fajl);
    if (niz_p != NULL)
        *niz_p = niz;
    return flag;
}
bool ucitaj_sve_tran(char* putanja, TRANSAKCIJA** niz_t, int *i) {
    if (!postoji(putanja))
        return false;
    FILE* fajl = fopen(putanja, "rb");
    TRANSAKCIJA t;
    bool flag = false;
    int kapacitet = 16;
    TRANSAKCIJA *niz = malloc(kapacitet*sizeof(TRANSAKCIJA));
    if (niz_t == NULL)
        free(niz);
    while (fread(&t,sizeof(t),1,fajl)) {
        flag = true;
        char mod[6];
        if (t.Promena == ULAZ)
            strcpy(mod,"ULAZ");
        else
            strcpy(mod,"IZLAZ");
        if (niz_t == NULL) {
            printf("Id:%u, PROMENA: %s, Kolicina: %u\n",t.Id,mod,t.Kolicina);
            continue;
        }
        if (*i >= kapacitet) {
            kapacitet*=2;
            TRANSAKCIJA *tmp = realloc(niz,kapacitet*sizeof(TRANSAKCIJA));
            niz = tmp;
        }
        niz[(*i)++] = t;

    }

    if (niz_t != NULL)
        *niz_t = niz;
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
bool ucitaj_Id_tran(char* putanja,unsigned id) {
    if (!postoji(putanja))
        return false;
    FILE * fajl = fopen(putanja,"rb");
    TRANSAKCIJA t;
    int i = 0;
    while (fread(&t, sizeof(t),1,fajl)) {
        if (t.Id == id) {
           i++;
        }
    }
    TRANSAKCIJA *t_niz = malloc(i*sizeof(TRANSAKCIJA));
    rewind(fajl);
    int j = 0;
    while (fread(&t, sizeof(t),1,fajl)) {
        if (t.Id == id) {
            t_niz[j++] = t;
        }
    }
    for (int j = 0; j < i;j++) {
        char mod[6];
        if (t_niz[j].Promena == ULAZ)
            strlcpy(mod,"ULAZ",sizeof(mod));
        else
            strlcpy(mod,"IZLAZ",sizeof(mod));
        printf("Id:%u, PROMENA: %s, Kolicina: %u\n",t_niz[j].Id,mod,t_niz[j].Kolicina);
    }
    free(t_niz);
    fclose(fajl);
    return true;

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
    sortiraj_fajl(putanja,sizeof(PROIZVOD),proizvod);
    return flag;
}
void sortiraj_fajl(char* putanja,size_t velicina_sloga, const Vrsta v) {
    if (!postoji(putanja))
        return;
    FILE * fajl = fopen(putanja,"rb");
    if (!fajl) return;
    if (fseek(fajl,0,SEEK_END)!= 0) {fclose(fajl);return ;}
    long velicina_fajla = ftell(fajl);
    long broj_slogova = (velicina_fajla/(long)velicina_sloga);
    if (velicina_fajla < 0) return;
    rewind(fajl);
    void *niz = malloc(broj_slogova*velicina_sloga);
    const int i = (int)broj_slogova;
    if (fread(niz,velicina_sloga,broj_slogova,fajl) != (size_t)broj_slogova) {
        free(niz);
        fclose(fajl);
        return;
    }
    fclose(fajl);
    fajl = fopen(putanja,"wb");
    if (v == transakcija) {
        qsort(niz,broj_slogova,velicina_sloga,poredi_tran);
        for (int j = 0;j < i;j++) {
            fwrite(&((TRANSAKCIJA*)niz)[j], sizeof(TRANSAKCIJA), 1, fajl);
        }
    }else {
        qsort(niz,broj_slogova,velicina_sloga,poredi_proiz);
        for (int j = 0;j < i;j++) {
            fwrite(&((PROIZVOD*)niz)[j], sizeof(PROIZVOD), 1, fajl);
        }
    }
    fclose(fajl);
    free(niz);
}//update maticne

void sumarna_transakciona_datoteka(TRANSAKCIJA** vraceni_niz, int* n) {
    PROIZVOD *niz_p = NULL;
    TRANSAKCIJA *niz_t = NULL;
    int t = 0;
    int p = 0;
    ucitaj_sve(mat_tek,&niz_p,&p);
    ucitaj_sve_tran(tran_dat,&niz_t,&t);

    TRANSAKCIJA* novi_niz =malloc(t*sizeof(TRANSAKCIJA));
    int z = 0;

    FILE* fajl = fopen(tran_tek,"wb");
    for (int i = 0;i < t;i++) {
        int _n = 0;
        TRANSAKCIJA *isti_id = malloc(t*sizeof(TRANSAKCIJA));
        if (sadrzi(novi_niz,niz_t[i].Id,z)) {
            free(isti_id);
            continue;
        }
        isti_id[_n++] = niz_t[i];
        for (int j = i+1; j<t;j++) {
            if (niz_t[i].Id == niz_t[j].Id)
                isti_id[_n++]= niz_t[j];
        }
        TRANSAKCIJA _t;
        _t.Kolicina = 0;
        int _suma = 0;
        for (int j = 0;j<_n;j++) {
            _suma += (int)isti_id[j].Kolicina * isti_id[j].Promena;
        }
        if (_suma < 0)
            _t.Promena = IZLAZ;
        else
            _t.Promena = ULAZ;
        _t.Kolicina = abs(_suma);
        _t.Id = isti_id->Id;
        novi_niz[z++] = _t;
        free(isti_id);
    }
    qsort(novi_niz,z,sizeof(TRANSAKCIJA),poredi_tran);
    *vraceni_niz = novi_niz;
    *n = z;
    for (int _i = 0;_i< *n;_i++) {
        fwrite(&novi_niz[_i],sizeof(TRANSAKCIJA),1,fajl);
    }
    fclose(fajl);
    free(niz_p);
    free(niz_t);


}

void spoji_sa_maticnom(TRANSAKCIJA *sumarni_niz, int s) {
    PROIZVOD *maticni_niz;
    int p = 0;
    ucitaj_sve(mat_tek, &maticni_niz, &p);
    PROIZVOD *novi_niz = malloc((p + s) * sizeof(PROIZVOD));
    int n = 0;

    PROIZVOD *novi_proizvodi = malloc(s * sizeof(PROIZVOD));
    int _privremeni = 0;
    for (int i = s - 1; i >= 0; i--) {
        int pozicija = 0;
        if (!sadrzi_p(maticni_niz, sumarni_niz[i].Id, p, &pozicija)) {
            if (sumarni_niz[i].Promena == IZLAZ) {
                //OBRADA GRESKE DA NE POSTOJI TAJ ELEMENT KOJI SE TRAZI.
                insert_u_izvestaj_greska(err_pro_rpt,&maticni_niz[i],&sumarni_niz[i],"Nepostojeci proizvod");
                izbaci_element_t(&sumarni_niz, i, &s);

            } else {
                //OVDE TREBA DODATI U MATICNU DATOTEKU PROIZVOD.
                char naziv[14];
                bool flag = false;
                while (flag == false) {
                    printf("INFO: Proizvod sa Id: %u ne postoji u maticnoj datoteci. Unesite naziv: ");
                    if (!fgets(naziv, sizeof naziv, stdin)) {
                        puts("ERROR: Pogresan format. pokusajte ponovo.");
                        continue;
                    }
                    if (!strchr(naziv, '\n')) {
                        puts("ERROR: Predugacak naziv (14). pokusajte ponovo.");
                        ocisti_bafer();
                        continue;
                    }
                    naziv[strcspn(naziv, "\n")] = '\0';
                    flag = true;
                }
                PROIZVOD temp;
                temp.Id = sumarni_niz[i].Id;
                strcpy(temp.Naziv, naziv);
                temp.Kolicina = sumarni_niz[i].Kolicina;
                if (!postoji(nov_pro_rpt)) {//nov proizvod
                    kreiraj_izvestaj(nov_pro_rpt);
                    insert_u_izvestaj_proizvod(nov_pro_rpt, &temp);
                }

                novi_proizvodi[_privremeni++] = temp;
            }
        }
    }
    for (int i = 0; i < p; i++) {
        bool nadjen = false;
        for (int j = 0; j < s; j++) {
            if (maticni_niz[i].Id == sumarni_niz[j].Id) {
                //slcuaj kada je sve normalno
                nadjen = true;
                int pozicija = 0;
                int suma = (int) novi_niz[n - 1].Kolicina + (int) sumarni_niz[j].Kolicina * sumarni_niz[j].Promena;
                if (suma >= 0) {
                    novi_niz[n++] = maticni_niz[i];
                    novi_niz[n - 1].Kolicina = suma;
                }else {
                    //greska, ima manje od ukupne kolicine
                    insert_u_izvestaj_greska(err_kol_rpt,&maticni_niz[i],&sumarni_niz[i],"Nepostojeca kolicina proizvoda");
                    novi_niz[n++] = maticni_niz[i];
                }
                break;
            }
        }
        if (!nadjen)
            novi_niz[n++] = maticni_niz[i];
    }
    for (int _i = 0; _i < _privremeni; _i++) {
        novi_niz[n++] = novi_proizvodi[_i];
    }
    kreiraj_datoteku(mat_nova,true);
    for (int _i = 0; _i < n; _i++) {
        insert_u_datoteku(mat_nova, &novi_niz[_i]);
    }
    free(novi_proizvodi);
    free(maticni_niz);
    free(novi_niz);
}



void update(char* putanja) {
    if (!postoji(mat_dat) || !postoji(tran_dat)) {
        printf("Datoteke ne postoje.");
        return;
    }
    kopiraj_datoteku(mat_dat,mat_tek);
    TRANSAKCIJA *sumarni_niz;
    int s = 0;
    sumarna_transakciona_datoteka(&sumarni_niz,&s);
    spoji_sa_maticnom(sumarni_niz,s);
    free(sumarni_niz);
    ucitaj_sve(mat_dat,NULL, NULL);
}