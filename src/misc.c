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
        case 1:
            puts("Овај случај је најједноставнији. Ажурира се производ који постоји у матичној датотеци,");
            puts("а количине су увек одговарајуће.");
            puts("");
            puts("Сценарио случаја:");
            puts("(а) Д.1. + Д.3. = И.1.");
            puts("(б) Д.1. + Д.4. = И.1.");
            puts("");
            puts("Вербални опис сценарија:");
            puts("(а) примљена количина производа се додаје на тренутно расположиву количину,");
            puts("    а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,");
            puts("(б) издата количина производа је мања од тренутно расположиве количине,");
            puts("    а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку.");
            puts("");
            puts("Демо подаци:");
            puts("");
            puts("Стара матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    150");
            puts("40   Pro_40    200");
            puts("50   Pro_50    250");
            puts("60   Pro_60    300");
            puts("70   Pro_70    350");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Трансакциона датотека: transakciona.dat");
            puts("Id   Promena   Kolicina");
            puts("60   ULAZ      150");
            puts("40   ULAZ      80");
            puts("60   ULAZ      50");
            puts("60   IZLAZ     100");
            puts("40   IZLAZ     50");
            puts("60   IZLAZ     150");
            puts("60   ULAZ      200");
            puts("40   IZLAZ     80");
            puts("60   ULAZ      20");
            puts("70   IZLAZ     120");
            puts("70   ULAZ      100");
            puts("70   IZLAZ     100");
            puts("70   ULAZ      50");
            puts("70   IZLAZ     50");
            puts("");
            puts("Сумарна трансакциона датотека: tran_210429.dat");
            puts("Id   Promena   Kolicina");
            puts("40   ULAZ      50");
            puts("60   IZLAZ     50");
            puts("70   ULAZ      0");
            puts("");
            puts("Нова матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    150");
            puts("40   Pro_40    250");
            puts("50   Pro_50    250");
            puts("60   Pro_60    250");
            puts("70   Pro_70    350");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Извештај о променама: prom_210429.rpt");
            puts("Id   Naziv     Tip   Kolicina   Nova_kolicina");
            puts("40   Pro_40    +     50         250");
            puts("60   Pro_60    -     50         250");
            puts("70   Pro_70    +     0          350");

            break;
        case 2:
            puts("Ажурира се производ који постоји у матичној датотеци, али се узима у обзир да се може");
            puts("десити издавање непостојеће количине.");
            puts("");
            puts("Сценарио случаја:");
            puts("(а) Д.1. + Д.3. = И.1.");
            puts("(б) Д.1. + Д.4. = И.1.");
            puts("(в) Д.1. + Д.4. = И.2.");
            puts("");
            puts("Вербални опис сценарија:");
            puts("(а) примљена количина производа се додаје на тренутно расположиву количину, а порука");
            puts("    о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,");
            puts("(б) издата количина производа је мања од тренутно расположиве количине, а порука");
            puts("    о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,");
            puts("(в) издата количина производа није мања од тренутно расположиве количине");
            puts("    (или је већа од тренутно расположиве количине), што је грешка;");
            puts("    операција се одбија, а порука о неуспешном ажурирању и разлогу грешке");
            puts("    се уписује у одговарајућу датотеку.");
            puts("");
            puts("Очигледно је да се овај случај може описати као:");
            puts("Случај #1 + издавање непостојеће количине производа");
            puts("");
            puts("Демо подаци:");
            puts("");
            puts("Стара матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    150");
            puts("40   Pro_40    200");
            puts("50   Pro_50    250");
            puts("60   Pro_60    300");
            puts("70   Pro_70    350");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Трансакциона датотека: transakciona.dat");
            puts("Id   Promena   Kolicina");
            puts("80   IZLAZ     50");
            puts("70   IZLAZ     400");
            puts("80   ULAZ      100");
            puts("90   IZLAZ     800");
            puts("60   IZLAZ     500");
            puts("20   IZLAZ     500");
            puts("30   ULAZ      100");
            puts("20   IZLAZ     300");
            puts("60   IZLAZ     300");
            puts("40   ULAZ      150");
            puts("50   IZLAZ     200");
            puts("40   IZLAZ     100");
            puts("50   IZLAZ     300");
            puts("50   IZLAZ     300");
            puts("30   IZLAZ     50");
            puts("90   ULAZ      800");
            puts("70   ULAZ      200");
            puts("");
            puts("Сумарна трансакциона датотека: tran_210429.dat");
            puts("Id   Promena   Kolicina");
            puts("20   IZLAZ     800");
            puts("30   ULAZ      50");
            puts("40   ULAZ      50");
            puts("50   IZLAZ     800");
            puts("60   IZLAZ     800");
            puts("70   IZLAZ     200");
            puts("80   ULAZ      50");
            puts("90   ULAZ      0");
            puts("");
            puts("Нова матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    200");
            puts("40   Pro_40    250");
            puts("50   Pro_50    250");
            puts("60   Pro_60    300");
            puts("70   Pro_70    150");
            puts("80   Pro_80    450");
            puts("90   Pro_90    450");
            puts("");
            puts("Извештај о променама: prom_210429.rpt");
            puts("Id   Naziv     Tip   Kolicina   Nova_kolicina");
            puts("30   Pro_30    +     50         200");
            puts("40   Pro_40    +     50         250");
            puts("70   Pro_70    -     200        150");
            puts("80   Pro_80    +     50         450");
            puts("90   Pro_90    +     0          450");
            puts("");
            puts("Извештај о грешкама: err_kol_210429.rpt");
            puts("Id   Naziv     Trenutna_kolicina   Tip   Kolicina   Greska");
            puts("20   Pro_20    100                  -     800       Nepostojeca kolicina proizvoda");
            puts("50   Pro_50    250                  -     800       Nepostojeca kolicina proizvoda");
            puts("60   Pro_60    300                  -     800       Nepostojeca kolicina proizvoda");
            break;
        case 3:
            puts("Ажурира се производ који постоји у матичној датотеци, али се узима у обзир да се може");
            puts("десити примање новог производа.");
            puts("");
            puts("Сценарио случаја:");
            puts("(а) Д.1. + Д.3. = И.1.");
            puts("(б) Д.1. + Д.4. = И.1.");
            puts("(в) Д.2. + Д.3. = И.1.");
            puts("");
            puts("Вербални опис сценарија:");
            puts("(а) примљена количина производа се додаје на тренутно расположиву количину,");
            puts("    а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,");
            puts("(б) издата количина производа је мања од тренутно расположиве количине,");
            puts("    а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,");
            puts("(в) примљена је количина производа који се не налази у матичној датотеци,");
            puts("    па се у матичну датотеку додаје нов производ са примљеном количином,");
            puts("    а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку.");
            puts("");
            puts("Опис случаја:");
            puts("Случај #1 + примање количине непостојећег производа");
            puts("=> додаје се нов производ у матичну датотеку");
            puts("");
            puts("Демо подаци:");
            puts("");
            puts("Стара матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    150");
            puts("40   Pro_40    200");
            puts("50   Pro_50    250");
            puts("60   Pro_60    300");
            puts("70   Pro_70    350");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Трансакциона датотека: transakciona.dat");
            puts("Id   Promena   Kolicina");
            puts("55   ULAZ      205");
            puts("95   ULAZ      295");
            puts("55   ULAZ      50");
            puts("45   ULAZ      245");
            puts("95   IZLAZ     15");
            puts("15   ULAZ      230");
            puts("10   ULAZ      190");
            puts("20   IZLAZ     100");
            puts("30   IZLAZ     50");
            puts("20   ULAZ      50");
            puts("35   ULAZ      285");
            puts("36   ULAZ      236");
            puts("35   IZLAZ     50");
            puts("37   ULAZ      240");
            puts("37   IZLAZ     3");
            puts("70   ULAZ      100");
            puts("10   IZLAZ     20");
            puts("10   ULAZ      40");
            puts("15   IZLAZ     15");
            puts("95   ULAZ      15");
            puts("");
            puts("Сумарна трансакциона датотека: tran_210429.dat");
            puts("Id   Promena   Kolicina");
            puts("10   ULAZ      210");
            puts("15   ULAZ      215");
            puts("20   IZLAZ     100");
            puts("30   IZLAZ     50");
            puts("35   ULAZ      235");
            puts("36   ULAZ      236");
            puts("37   ULAZ      237");
            puts("45   ULAZ      245");
            puts("55   ULAZ      255");
            puts("70   ULAZ      100");
            puts("95   ULAZ      295");
            puts("");
            puts("Нова матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("10   Pro_10    210");
            puts("15   Pro_15    215");
            puts("20   Pro_20    50");
            puts("30   Pro_30    100");
            puts("35   Pro_35    235");
            puts("36   Pro_36    236");
            puts("37   Pro_37    237");
            puts("40   Pro_40    200");
            puts("45   Pro_45    245");
            puts("50   Pro_50    250");
            puts("55   Pro_55    255");
            puts("60   Pro_60    300");
            puts("70   Pro_70    450");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("95   Pro_95    295");
            puts("");
            puts("Извештај о променама: prom_210429.rpt");
            puts("Id   Naziv     Tip   Kolicina   Nova_kolicina");
            puts("20   Pro_20    -     50         50");
            puts("30   Pro_30    -     50         100");
            puts("70   Pro_70    +     100        450");
            puts("");
            puts("Извештај о новим производима: nov_pro_210429.rpt");
            puts("Id   Naziv     Kolicina");
            puts("10   Pro_10    210");
            puts("15   Pro_15    215");
            puts("35   Pro_35    235");
            puts("36   Pro_36    236");
            puts("37   Pro_37    237");
            puts("45   Pro_45    245");
            puts("55   Pro_55    255");
            puts("95   Pro_95    295");
            break;
        case 4:
            puts("Ажурира се производ који постоји у матичној датотеци, али се узима у обзир да се може");
            puts("десити издавање количине непостојећег производа.");
            puts("");
            puts("Сценарио случаја:");
            puts("(а) Д.1. + Д.3. = И.1.");
            puts("(б) Д.1. + Д.4. = И.1.");
            puts("(в) Д.2. + Д.4. = И.2.");
            puts("");
            puts("Вербални опис сценарија:");
            puts("(а) примљена количина производа се додаје на тренутно расположиву количину,");
            puts("    а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,");
            puts("(б) издата количина производа је мања од тренутно расположиве количине,");
            puts("    а порука о успешном ажурирању и насталој промени се уписује у одговарајућу датотеку,");
            puts("(в) издаје се производ који се не налази у матичној датотеци, што је грешка;");
            puts("    операција се одбија и уписује се порука о грешци.");
            puts("");
            puts("Опис случаја:");
            puts("Случај #1 + издавање количине непостојећег производа");
            puts("");
            puts("Стара матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    150");
            puts("40   Pro_40    200");
            puts("50   Pro_50    250");
            puts("60   Pro_60    300");
            puts("70   Pro_70    350");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Трансакциона датотека: transakciona.dat");
            puts("Id   Promena   Kolicina");
            puts("30   ULAZ      100");
            puts("92   IZLAZ     40");
            puts("30   IZLAZ     20");
            puts("23   IZLAZ     40");
            puts("50   ULAZ      20");
            puts("12   IZLAZ     40");
            puts("22   IZLAZ     20");
            puts("22   IZLAZ     20");
            puts("");
            puts("Сумарна трансакциона датотека: tran_210429.dat");
            puts("Id   Promena   Kolicina");
            puts("12   IZLAZ     40");
            puts("22   IZLAZ     40");
            puts("23   IZLAZ     40");
            puts("30   ULAZ      80");
            puts("50   ULAZ      20");
            puts("92   IZLAZ     40");
            puts("");
            puts("Нова матична датотека: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    230");
            puts("40   Pro_40    200");
            puts("50   Pro_50    270");
            puts("60   Pro_60    300");
            puts("70   Pro_70    350");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Извештај о променама: prom_210429.rpt");
            puts("Id   Naziv     Tip   Kolicina   Nova_kolicina");
            puts("30   Pro_30    +     80         230");
            puts("50   Pro_50    +     20         270");
            puts("");
            puts("Извештај о грешкама: err_pro_210429.rpt");
            puts("Id   Promena   Kolicina   Greska");
            puts("12   IZLAZ     40         Nepostojeci proizvod.");
            puts("22   IZLAZ     40         Nepostojeci proizvod.");
            puts("23   IZLAZ     40         Nepostojeci proizvod.");
            puts("92   IZLAZ     40         Nepostojeci proizvod.");
            break;
        case 5:
            puts("5. Sveobuhvatni slucaj");
            puts("Azurira se proizvod u maticnoj datoteci uz razmatranje svih mogucih slucajeva.");
            puts("");
            puts("Scenario slucaja:");
            puts("(a) D.1. + D.3. = I.1.");
            puts("(b) D.1. + D.4. = I.1.");
            puts("(v) D.1. + D.4. = I.2.");
            puts("(g) D.2. + D.3. = I.1.");
            puts("(d) D.2. + D.4. = I.2.");
            puts("");
            puts("Verbalni opis scenarija:");
            puts("(a) Primljena kolicina se dodaje na postojecu kolicinu (uspesno azuriranje).");
            puts("(b) Izdata kolicina je manja od raspolozive (uspesno azuriranje).");
            puts("(v) Izdata kolicina je veca ili jednaka raspolozivoj (greska).");
            puts("(g) Primljen je novi proizvod – dodaje se u maticnu datoteku.");
            puts("(d) Izdat je nepostojeci proizvod (greska).");
            puts("");
            puts("Stara maticna datoteka: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("20   Pro_20    100");
            puts("30   Pro_30    150");
            puts("40   Pro_40    200");
            puts("50   Pro_50    250");
            puts("60   Pro_60    300");
            puts("70   Pro_70    350");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Transakciona datoteka: transakciona.dat");
            puts("Id   Promena   Kolicina");
            puts("20   ULAZ      50");
            puts("70   IZLAZ     50");
            puts("90   IZLAZ     50");
            puts("50   IZLAZ     800");
            puts("60   IZLAZ     800");
            puts("35   ULAZ      150");
            puts("15   ULAZ      150");
            puts("22   IZLAZ     175");
            puts("92   IZLAZ     175");
            puts("20   ULAZ      50");
            puts("70   IZLAZ     50");
            puts("90   ULAZ      50");
            puts("");
            puts("Sumarna transakciona datoteka: tran_210429.dat");
            puts("Id   Promena   Kolicina");
            puts("15   ULAZ      150");
            puts("20   ULAZ      100");
            puts("22   IZLAZ     175");
            puts("35   ULAZ      150");
            puts("50   IZLAZ     800");
            puts("60   IZLAZ     800");
            puts("70   IZLAZ     100");
            puts("90   ULAZ      0");
            puts("92   IZLAZ     175");
            puts("");
            puts("Nova maticna datoteka: maticna.dat");
            puts("Id   Naziv     Kolicina");
            puts("15   Pro_15    150");
            puts("20   Pro_20    200");
            puts("30   Pro_30    150");
            puts("35   Pro_35    150");
            puts("40   Pro_40    200");
            puts("50   Pro_50    250");
            puts("60   Pro_60    300");
            puts("70   Pro_70    250");
            puts("80   Pro_80    400");
            puts("90   Pro_90    450");
            puts("");
            puts("Izvestaj o promenama: prom_210429.rpt");
            puts("Id   Naziv     Tip   Kolicina   Nova_kolicina");
            puts("20   Pro_20    +     100        200");
            puts("70   Pro_70    +     100        250");
            puts("90   Pro_90    -     0          450");
            puts("");
            puts("Izvestaj o greskama (nepostojeci proizvod): err_pro_210429.rpt");
            puts("Id   Promena   Kolicina   Greska");
            puts("22   IZLAZ     175        Nepostojeci proizvod.");
            puts("92   IZLAZ     175        Nepostojeci proizvod.");
            puts("");
            puts("Izvestaj o novim proizvodima: nov_pro_210429.rpt");
            puts("Id   Proizvod  Kolicina");
            puts("15   Pro_15    150");
            puts("35   Pro_35    150");
            puts("");
            puts("Izvestaj o greskama (nepostojeca kolicina): err_kol_210429.rpt");
            puts("Id   Naziv     Trenutna_kolicina   Promena   Kolicina   Greska");
            puts("50   Pro_50    250                  -         800       Nepostojeca kolicina proizvoda.");
            puts("60   Pro_60    300                  -         800       Nepostojeca kolicina proizvoda.");

            break;
    }
}
