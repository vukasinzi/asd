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
    switch (arg) {
        case 1:
            kopiraj_datoteku("../demo/demo_tran1.dat",tran_dat);
            kopiraj_datoteku("../demo/demo_maticna.dat",mat_dat);
            break;
        case 2:
            kopiraj_datoteku("../demo/demo_tran2.dat",tran_dat);
            kopiraj_datoteku("../demo/demo_maticna.dat",mat_dat);
            break;
        case 3:
            kopiraj_datoteku("../demo/demo_tran3.dat",tran_dat);
            kopiraj_datoteku("../demo/demo_maticna.dat",mat_dat);
            break;
        case 4:
            kopiraj_datoteku("../demo/demo_tran4.dat",tran_dat);
            kopiraj_datoteku("../demo/demo_maticna.dat",mat_dat);
            break;
        case 5:
            kopiraj_datoteku("../demo/demo_tran5.dat",tran_dat);
            kopiraj_datoteku("../demo/demo_maticna.dat",mat_dat);
            break;
        default:
            break;
    }
}

void ucitaj(int izbor) {
    switch (izbor) {
        case 1: printf(
                "Овај случај је најједноставнији. Ажурира се производ који постоји у матичној датотеци, а количине су увек одговарајуће.\nСценарио случаја:\n(а) Д.1. + Д.3. = И.1.\n(б) Д.1. + Д.4. = И.1.\n\nВербални опис сценарија:\n(а) примљена количина производа се додаје на тренутно расположиву количину, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,\n(б) издата количина производа је мања од тренутно расположиве количине, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку.\n\nДемо подаци:\nСтара матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    150\n40   Pro_40    200\n50   Pro_50    250\n60   Pro_60    300\n70   Pro_70    350\n80   Pro_80    400\n90   Pro_90    450\n\nТрансакциона датотека: transakciona.dat\nId   Promena   Kolicina\n60   ULAZ      150\n40   ULAZ      80\n60   ULAZ      50\n60   IZLAZ     100\n40   IZLAZ     50\n60   IZLAZ     150\n60   ULAZ      200\n40   IZLAZ     80\n60   ULAZ      20\n70   IZLAZ     120\n70   ULAZ      100\n70   IZLAZ     100\n70   ULAZ      50\n70   IZLAZ     50\n\nСумарна трансакциона датотека: tran_210429.dat\nId   Promena   Kolicina\n40   ULAZ      50\n60   IZLAZ     50\n70   ULAZ      0\n\nНова матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    150\n40   Pro_40    250\n50   Pro_50    250\n60   Pro_60    250\n70   Pro_70    350\n80   Pro_80    400\n90   Pro_90    450\n\nИзвештај о променама: prom_210429.rpt\nId   Naziv     Tip   Kolicina   Nova_kolicina\n40   Pro_40    +     50         250\n60   Pro_60    -     50         250\n70   Pro_70    +     0          350");
            break;

        case 2: printf(
                "Ажурира се производ који постоји у матичној датотеци, али се узима у обзир да се може десити издавање непостојеће количине.\n\nСценарио случаја:\n(а) Д.1. + Д.3. = И.1.\n(б) Д.1. + Д.4. = И.1.\n(в) Д.1. + Д.4. = И.2.\n\nВербални опис сценарија:\n(а) примљена количина производа се додаје на тренутно расположиву количину, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,\n(б) издата количина производа је мања од тренутно расположиве количине, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,\n(в) издата количина производа није мања од тренутно расположиве количине (или је већа од тренутно расположиве количине), што је грешка; операција се одбија, а порука о неуспешном ажурирању и разлогу грешке се уписује у одговарајућу датотеку.\n\nОчигледно је да се овај случај може описати као:\nСлучај #1 + издавање непостојеће количине производа\n\nДемо подаци:\nСтара матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    150\n40   Pro_40    200\n50   Pro_50    250\n60   Pro_60    300\n70   Pro_70    350\n80   Pro_80    400\n90   Pro_90    450\n\nТрансакциона датотека: transakciona.dat\nId   Promena   Kolicina\n80   IZLAZ     50\n70   IZLAZ     400\n80   ULAZ      100\n90   IZLAZ     800\n60   IZLAZ     500\n20   IZLAZ     500\n30   ULAZ      100\n20   IZLAZ     300\n60   IZLAZ     300\n40   ULAZ      150\n50   IZLAZ     200\n40   IZLAZ     100\n50   IZLAZ     300\n50   IZLAZ     300\n30   IZLAZ     50\n90   ULAZ      800\n70   ULAZ      200\n\nСумарна трансакциона датотека: tran_210429.dat\nId   Promena   Kolicina\n20   IZLAZ     800\n30   ULAZ      50\n40   ULAZ      50\n50   IZLAZ     800\n60   IZLAZ     800\n70   IZLAZ     200\n80   ULAZ      50\n90   ULAZ      0\n\nНова матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    200\n40   Pro_40    250\n50   Pro_50    250\n60   Pro_60    300\n70   Pro_70    150\n80   Pro_80    450\n90   Pro_90    450\n\nИзвештај о променама: prom_210429.rpt\nId   Naziv     Tip   Kolicina   Nova_kolicina\n30   Pro_30    +     50         200\n40   Pro_40    +     50         250\n70   Pro_70    -     200        150\n80   Pro_80    +     50         450\n90   Pro_90    +     0          450\n\nИзвештај о грешкама: err_kol_210429.rpt\nId   Naziv     Trenutna_kolicina   Tip   Kolicina   Greska\n20   Pro_20    100                  -     800       Nepostojeca kolicina proizvoda\n50   Pro_50    250                  -     800       Nepostojeca kolicina proizvoda\n60   Pro_60    300                  -     800       Nepostojeca kolicina proizvoda\n");
            break;
        case 3: printf(
                "Ажурира се производ који постоји у матичној датотеци, али се узима у обзир да се може десити примање новог производа.\n\nСценарио случаја:\n(а) Д.1. + Д.3. = И.1.\n(б) Д.1. + Д.4. = И.1.\n(в) Д.2. + Д.3. = И.1.\n\nВербални опис сценарија:\n(а) примљена количина производа се додаје на тренутно расположиву количину, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,\n(б) издата количина производа је мања од тренутно расположиве количине, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,\n(в) примљена је количина производа који се не налази у матичној датотеци, па се у матичну датотеку додаје нов производ са примљеном количином, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку.\n\nОпис случаја:\nСлучај #1 + примање количине непостојећег производа\n=> додаје се нов производ у матичну датотеку\n\nДемо подаци:\nСтара матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    150\n40   Pro_40    200\n50   Pro_50    250\n60   Pro_60    300\n70   Pro_70    350\n80   Pro_80    400\n90   Pro_90    450\n\nТрансакциона датотека: transakciona.dat\nId   Promena   Kolicina\n55   ULAZ      205\n95   ULAZ      295\n55   ULAZ      50\n45   ULAZ      245\n95   IZLAZ     15\n15   ULAZ      230\n10   ULAZ      190\n20   IZLAZ     100\n30   IZLAZ     50\n20   ULAZ      50\n35   ULAZ      285\n36   ULAZ      236\n35   IZLAZ     50\n37   ULAZ      240\n37   IZLAZ     3\n70   ULAZ      100\n10   IZLAZ     20\n10   ULAZ      40\n15   IZLAZ     15\n95   ULAZ      15\n\nСумарна трансакциона датотека: tran_210429.dat\nId   Promena   Kolicina\n10   ULAZ      210\n15   ULAZ      215\n20   IZLAZ     100\n30   IZLAZ     50\n35   ULAZ      235\n36   ULAZ      236\n37   ULAZ      237\n45   ULAZ      245\n55   ULAZ      255\n70   ULAZ      100\n95   ULAZ      295\n\nНова матична датотека: maticna.dat\nId   Naziv     Kolicina\n10   Pro_10    210\n15   Pro_15    215\n20   Pro_20    50\n30   Pro_30    100\n35   Pro_35    235\n36   Pro_36    236\n37   Pro_37    237\n40   Pro_40    200\n45   Pro_45    245\n50   Pro_50    250\n55   Pro_55    255\n60   Pro_60    300\n70   Pro_70    450\n80   Pro_80    400\n90   Pro_90    450\n95   Pro_95    295\n\nИзвештај о променама: prom_210429.rpt\nId   Naziv     Tip   Kolicina   Nova_kolicina\n20   Pro_20    -     50         50\n30   Pro_30    -     50         100\n70   Pro_70    +     100        450\n\nИзвештај о новим производима: nov_pro_210429.rpt\nId   Naziv     Kolicina\n10   Pro_10    210\n15   Pro_15    215\n35   Pro_35    235\n36   Pro_36    236\n37   Pro_37    237\n45   Pro_45    245\n55   Pro_55    255\n95   Pro_95    295\n");
            break;

        case 4: printf(
                "Ажурира се производ који постоји у матичној датотеци, али се узима у обзир да се може десити издавање количине непостојећег производа.\n\nСценарио случаја:\n(а) Д.1. + Д.3. = И.1.\n(б) Д.1. + Д.4. = И.1.\n(в) Д.2. + Д.4. = И.2.\n\nВербални опис сценарија:\n(а) примљена количина производа се додаје на тренутно расположиву количину, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,\n(б) издата количина производа је мања од тренутно расположиве количине, а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,\n(в) издаје се производ који се не налази у матичној датотеци, што је грешка; операција се одбија и уписује се порука о грешци.\n\nОпис случаја:\nСлучај #1 + издавање количине непостојећег производа\n\nСтара матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    150\n40   Pro_40    200\n50   Pro_50    250\n60   Pro_60    300\n70   Pro_70    350\n80   Pro_80    400\n90   Pro_90    450\n\nТрансакциона датотека: transakciona.dat\nId   Promena   Kolicina\n30   ULAZ      100\n92   IZLAZ     40\n30   IZLAZ     20\n23   IZLAZ     40\n50   ULAZ      20\n12   IZLAZ     40\n22   IZLAZ     20\n22   IZLAZ     20\n\nСумарна трансакциона датотека: tran_210429.dat\nId   Promena   Kolicina\n12   IZLAZ     40\n22   IZLAZ     40\n23   IZLAZ     40\n30   ULAZ      80\n50   ULAZ      20\n92   IZLAZ     40\n\nНова матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    230\n40   Pro_40    200\n50   Pro_50    270\n60   Pro_60    300\n70   Pro_70    350\n80   Pro_80    400\n90   Pro_90    450\n\nИзвештај о променама: prom_210429.rpt\nId   Naziv     Tip   Kolicina   Nova_kolicina\n30   Pro_30    +     80         230\n50   Pro_50    +     20         270\n\nИзвештај о грешкама: err_pro_210429.rpt\nId   Promena   Kolicina   Greska\n12   IZLAZ     40         Nepostojeci proizvod.\n22   IZLAZ     40         Nepostojeci proizvod.\n23   IZLAZ     40         Nepostojeci proizvod.\n92   IZLAZ     40         Nepostojeci proizvod.\n");
            break;

        case 5: printf(
                "5. Свеобухватни случај\nАжурира се производ у матичној датотеци уз разматрање свих могућих случајева.\n\nСценарио случаја:\n(a) D.1. + D.3. = I.1.\n(b) D.1. + D.4. = I.1.\n(v) D.1. + D.4. = I.2.\n(g) D.2. + D.3. = I.1.\n(d) D.2. + D.4. = I.2.\n\nВербални опис сценарија:\n(a) Примљена количина се додаје на постојећу количину (успешно ажурирање).\n(b) Издата количина је мања од расположиве (успешно ажурирање).\n(v) Издата количина је већа или једнака расположивој (грешка).\n(g) Примљен је нови производ – додаје се у матичну датотеку.\n(d) Издат је непостојећи производ (грешка).\n\nСтара матична датотека: maticna.dat\nId   Naziv     Kolicina\n20   Pro_20    100\n30   Pro_30    150\n40   Pro_40    200\n50   Pro_50    250\n60   Pro_60    300\n70   Pro_70    350\n80   Pro_80    400\n90   Pro_90    450\n\nТрансакциона датотека: transakciona.dat\nId   Promena   Kolicina\n20   ULAZ      50\n70   IZLAZ     50\n90   IZLAZ     50\n50   IZLAZ     800\n60   IZLAZ     800\n35   ULAZ      150\n15   ULAZ      150\n22   IZLAZ     175\n92   IZLAZ     175\n20   ULAZ      50\n70   IZLAZ     50\n90   ULAZ      50\n\nСумарна трансакциона датотека: tran_210429.dat\nId   Promena   Kolicina\n15   ULAZ      150\n20   ULAZ      100\n22   IZLAZ     175\n35   ULAZ      150\n50   IZLAZ     800\n60   IZLAZ     800\n70   IZLAZ     100\n90   ULAZ      0\n92   IZLAZ     175\n\nНова матична датотека: maticna.dat\nId   Naziv     Kolicina\n15   Pro_15    150\n20   Pro_20    200\n30   Pro_30    150\n35   Pro_35    150\n40   Pro_40    200\n50   Pro_50    250\n60   Pro_60    300\n70   Pro_70    250\n80   Pro_80    400\n90   Pro_90    450\n\nИзвештај о променама: prom_210429.rpt\nId   Naziv     Tip   Kolicina   Nova_kolicina\n20   Pro_20    +     100        200\n70   Pro_70    +     100        250\n90   Pro_90    -     0          450\n\nИзвештај о грешкама (непостојећи производ): err_pro_210429.rpt\nId   Promena   Kolicina   Greska\n22   IZLAZ     175        Nepostojeci proizvod.\n92   IZLAZ     175        Nepostojeci proizvod.\n\nИзвештај о новим производима: nov_pro_210429.rpt\nId   Proizvod  Kolicina\n15   Pro_15    150\n35   Pro_35    150\n\nИзвештај о грешкама (непостојећа количина): err_kol_210429.rpt\nId   Naziv     Trenutna_kolicina   Promena   Kolicina   Greska\n50   Pro_50    250                  -         800       Nepostojeca kolicina proizvoda.\n60   Pro_60    300                  -         800       Nepostojeca kolicina proizvoda.\n");
            break;
    }
}
