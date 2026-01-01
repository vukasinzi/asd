#ifndef defs_H
#define defs_H


extern char mat_dat[256];
extern char tran_dat[256];
extern char mat_tek[256];
extern char tran_tek[256];
extern char mat_nova[256];
extern char prom_rpt[256];
extern char err_kol_rpt[256];
extern char nov_pro_rpt[256];
extern char err_pro_rpt[256];

//enumi
typedef enum menu {
    glavni_meni,
    transakcioni_meni,
    maticni_meni,
    pomocni_meni
}Menu;
typedef enum promena {
    IZLAZ = -1,
    ULAZ = 1
} PROMENA;
//proizvodi
typedef struct proizvod {
    unsigned Id;
    char Naziv[15];
    unsigned Kolicina;
} PROIZVOD;

typedef struct transakcija {
    unsigned Id;
    PROMENA Promena;
    unsigned Kolicina;
} TRANSAKCIJA;
#endif
