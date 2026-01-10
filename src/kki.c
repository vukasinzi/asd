#include <stdio.h>
#include "kki.h"
#include <string.h>
#include <stdbool.h>
#include "datoteka.h"
#include "defs.h"
#include "misc.h"

int trenutno = 0;
int arg = 0;

void ispis_azuriranje() {
    puts("Naziv projekta: ASD1");
    puts("");
    puts("Problem:");
    puts("- oblast: klasicna obrada podataka (obrada podataka zasnovana na datotekama)");
    puts("(file-based data processing)");
    puts("- tema: azuriranje serijske (sortirane redne) datoteke (ASD)");
    puts("(updating a serial /sorted regular/ file)");
    puts("");
    puts("Zahtev:");
    puts("Neophodno je resiti problem azuriranja serijske datoteke.");
    puts("Date su dve datoteke:");
    puts("(1) maticna datoteka, koja sadrzi podatke o proizvodima");
    puts("(identifikator, naziv i kolicina)");
    puts("i");
    puts("(2) transakciona datoteka, koja sadrzi podatke o nastalim promenama");
    puts("nad proizvodima.");
    puts("");
    puts("Maticna datoteka je uredjena (sortirana) po identifikatoru proizvoda,");
    puts("u rastucem redosledu (sortirana redna datoteka).");
    puts("");
    puts("U transakcionu datoteku se hronoloski upisuju promene");
    puts("obavljene nad proizvodima (redna datoteka).");
    puts("ULAZ znaci primanje novih proizvoda (povecanje kolicine),");
    puts("a IZLAZ znaci izdavanje postojecih proizvoda (smanjenje kolicine).");
    puts("Ova datoteka nije uredjena.");
    puts("");
    puts("Kada se zavrsi sa upisom promena u transakcionu datoteku");
    puts("(recimo na kraju dana), kreira se nova transakciona datoteka");
    puts("koja sadrzi sumarne podatke o nastalim promenama.");
    puts("");
    puts("Na primer, za proizvod Id = 40 su se u toku dana desile sledece promene:");
    puts("ULAZ 20, IZLAZ 30, ULAZ 40, IZLAZ 50.");
    puts("");
    puts("U sumarnoj transakcionoj datoteci (datoteci dnevnih promena,");
    puts("krace: datoteci promena) naci ce se samo jedan slog");
    puts("za proizvod Id = 40: IZLAZ 20.");
    puts("");
    puts("Na isti nacin ce se kreirati po jedan slog za sve proizvode");
    puts("za koje su se desile promene u jednom danu.");
    puts("");
    puts("Datoteka promena je uredjena po identifikatoru proizvoda,");
    puts("kao i maticna datoteka (sortirana redna datoteka).");
    puts("");
    puts("Sada se moze pristupiti azuriranju maticne datoteke,");
    puts("koje se obavlja dnevno.");
    puts("");
    puts("Moguci su sledeci dogadjaji:");
    puts("D.1. Pokusava se azuriranje proizvoda koji postoji u maticnoj datoteci");
    puts("D.2. Pokusava se azuriranje proizvoda koji ne postoji u maticnoj datoteci");
    puts("D.3. Pokusava se povecanje kolicine proizvoda");
    puts("D.4. Pokusava se smanjenje kolicine proizvoda");
    puts("");
    puts("Koji mogu da imaju sledece ishode:");
    puts("I.1. Uspesan pokusaj azuriranja:");
    puts("proizvod se azurira, a poruka o nastaloj promeni");
    puts("se upisuje u odgovarajucu datoteku");
    puts("");
    puts("I.2. Neuspesan pokusaj azuriranja:");
    puts("prijavljuje se greska, a poruka o razlogu nastale greske");
    puts("se upisuje u odgovarajucu datoteku");
    puts("");
    puts("Na osnovu prethodnog, uocavamo sledece slucajeve azuriranja:");
    puts("1. Osnovni slucaj");
    puts("2. Nepostojeca kolicina");
    puts("(izdavanje nepostojece kolicine postojeceg proizvoda)");
    puts("3. Nov proizvod");
    puts("(prijem kolicine nepostojeceg proizvoda)");
    puts("4. Nepostojeci proizvod");
    puts("(izdavanje kolicine nepostojeceg proizvoda)");
    puts("5. Sveobuhvatni slucaj");
}


void menu_ispis(const Menu m)
{
    switch (m) {
        case glavni_meni:
            ocisti_ekran();
            char dt[7];
            char date[9];
            datum(dt);
            sprintf(date, "%c%c.%c%c.%c%c", dt[0], dt[1], dt[2], dt[3], dt[4], dt[5]);
            puts("************************************************************");
            puts("* Aplikacija: ASD *");
            puts("* Opis: Azuriranje serijske (sortirane redne) datoteke *");
            puts("* Verzija: 1.0 *");
            puts("* Upotreba: asd.exe [-d[1|2|3|4|5]] *");
            puts("* 1 - demo za prvi slucaj azuriranja *");
            puts("* 2 - demo za drugi slucaj azuriranja *");
            printf("* Datum: %s. *\n",date);
            puts("* Autor: Vukašin Živaljević vz20220281@student.fon.bg.ac.rs *");
            puts("* Mentor: Saša D. Lazarević, slazar@fon.rs *");
            puts("************************************************************");
            puts("GLAVNI MENI");
            puts("==============================");
            puts("0. Kraj rada");
            puts("1. Rad sa transakcionom datotekom");
            puts("2. Rad sa maticnom datotekom");
            puts("3. Pomoc");

            break;

        case transakcioni_meni:

            puts("====================================================================");
            puts("MENI Transakciona datoteka");
            puts("====================================================================");
            puts("0. Povratak");
            puts("1. Create ::= Kreiranje nove transakcione datoteke");
            puts("2. Drop ::= Unistavanje postojece transakcione datoteke");
            puts("3. Insert ::= Dodavanje nove transakcije");
            puts("4. Select All ::= Prikazivanje svih transakcija");
            puts("5. Select Id ::= Prikazivanje svih transakcija jednog proizvoda");

            break;

        case maticni_meni:

            puts("================================================================================");
            puts("MENI Maticna datoteka");
            puts("================================================================================");
            puts("0. Povratak");
            puts("1. Create ::= Kreiranje nove maticne datoteke");
            puts("2. Drop ::= Unistavanje postojece maticne datoteke");
            puts("3. Insert ::= Dodavanje novog proizvoda");
            puts("4. Delete ::= Brisanje postojeceg proizvoda");
            puts("5. Update All ::= Azuriranje maticne datoteke upotrebom transakcione datoteke");
            puts("6. Update Id ::= Azuriranje jednog proizvoda");
            puts("7. Select All ::= Prikazivanje svih proizvoda");
            puts("8. Select Id ::= Prikazivanje jednog proizvoda");

            break;

        case pomocni_meni:
            puts("==================================");
            puts("MENI Pomoc");
            puts("==================================");
            puts("0. Povratak");
            puts("1. O azuriranju serijske datoteke");
            puts("2. Demo");
            puts("3. O nama");

            break;
        case demo_podmeni:
            puts("=========================");
            puts("MENI Demo");
            puts("=========================");
            puts("0. Povratak");
            puts("1. Osnovni slucaj");
            puts("2. Nepostojeca kolicina");
            puts("3. Nov proizvod");
            puts("4. Nepostojeci proizvod");
            puts("5. Sveobuhvatni slucaj");
            break;
    }
}

Menu stanje = glavni_meni;

void transakcioni_podmeni(int izbor) {
    trenutno = 1;
    switch (izbor) {
        case 0:
            stanje = glavni_meni;
            trenutno = 0;
            return;
        case 1: //create trans dat
            if (kreiraj_datoteku(tran_dat,false))
                puts("INFO: Transakciona datoteka je kreirana.");
            else
                puts("ERROR: Transakciona datoteka nije kreirana.");
            break;
        case 2: //drop
            if (unisti_datoteku(tran_dat))
                puts("INFO: Transakciona datoteka je obrisana.");
            else
                puts("ERROR: Transakciona datoteka nije obrisana.");
            break;
        case 3: //insert

            TRANSAKCIJA t;
            printf("Unesite id: ");
            if (scanf("%u",&t.Id)!= 1)
            {
                ocisti_bafer();
                puts("ERROR: Pogresan format. akcija se obustavlja.");
                break;
            }
            if (t.Id == 0) {
                puts("ERROR: PREKID");
                ocisti_bafer();
                break;
            }
            ocisti_bafer();

            printf("Unesite naziv promene (1 ULAZ, -1 IZLAZ): ");
            if (scanf("%d",&t.Promena)!= 1 || (t.Promena != 1 && t.Promena != -1))
            {
                ocisti_bafer();
                puts("ERROR: Pogresan format. Promena mora biti 1 ili -1");
                break;
            }
            ocisti_bafer();

            printf("Unesite kolicinu: ");
            if (scanf("%u",&t.Kolicina)!= 1)
            {
                ocisti_bafer();
                puts("ERROR: Pogresan format. Kolicina mora biti broj.");
                break;
            }
            ocisti_bafer();
            if (insert_u_datoteku_tran(tran_dat,&t))
                puts("INFO: Unesen proizvod u transakcionu datoteku.");
            else
                puts("ERROR: Greska pri unosu u transakcionu datoteku.");

            break;
        case 4: //select
            if (!ucitaj_sve_tran(tran_dat,NULL,NULL))
                puts("ERROR: Greska pri citanju transakcione datoteke.");
            break;
        case 5: //select id
            printf("Unesite id po kome pretrazujete: ");
            unsigned id2;
            if (scanf("%u",&id2) != 1) {
                ocisti_bafer();
                puts("ERROR: Pogresan format. Promena mora biti 1 ili -1");
                break;
            }
            ocisti_bafer();
            if (!ucitaj_Id_tran(tran_dat,id2))
                puts("ERROR: Greska pri citanju transakcione datoteke.");
            break;
        default:
            puts("ERROR: Selektujte odgovarajucu opciju.");
            break;

    }

}
//################################################################3MATICNA####################################################################
void maticni_podmeni(int izbor) {
    trenutno = 1;
    switch (izbor) {
        case 0:
            stanje = glavni_meni;
            trenutno = 0;
            return;
        case 1:
            if (kreiraj_datoteku(mat_dat,false))
                puts("INFO: Maticna datoteka je kreirana.");
            else
                puts("ERROR: Maticna datoteka nije kreirana.");
            break;
        case 2: //drop
            if (unisti_datoteku(mat_dat))
                puts("INFO: Maticna datoteka je obrisana.");
            else
                puts("ERROR: Maticna datoteka nije obrisana.");

            break;
        case 3: //insert
            PROIZVOD p;
            printf("Unesite id: ");
            if (scanf("%u",&p.Id)!= 1)
            {
                ocisti_bafer();
                puts("ERROR: Pogresan format. akcija se obustavlja.");
                break;
            }
            if (p.Id == 0) {
                puts("ERROR: PREKID");
                ocisti_bafer();
                break;
            }
            ocisti_bafer();
            printf("Unesite naziv proizvoda: ");
            if (!fgets(p.Naziv, sizeof p.Naziv, stdin)) {
                puts("ERROR: Pogresan format. akcija se obustavlja.");
                break;
            }
            if (!strchr(p.Naziv,'\n')) {
                puts("ERROR: Predugacak naziv (14). akcija se obustavlja.");
                ocisti_bafer();
                break;
            }
            p.Naziv[strcspn(p.Naziv, "\n")] = '\0';

            printf("Unesite kolicinu: ");
            if (scanf("%u",&p.Kolicina)!= 1)
            {
                ocisti_bafer();
                puts("ERROR: Pogresan format. akcija se obustavlja.");
                break;
            }
            ocisti_bafer();
            if (insert_u_datoteku(mat_dat,&p))
                puts("INFO: Unesen proizvod u maticnu datoteku.");
            else
                puts("ERROR: Greska pri unosu u maticnu datoteku.");
            break;
        case 4: //delete
            printf("Unesite id proizvoda kojeg brisete: ");
            unsigned id;
            if (scanf("%u", &id) != 1) {
                puts("ERROR: Unesite broj.");
                ocisti_bafer();
                break;
            }
            ocisti_bafer();
            if (!obrisi_Id(mat_dat,id))
                puts("ERROR: Greska pri citanju maticne datoteke.");
            else
                printf("INFO: Uspesno obrisan proizvod sa id: %d\n",id);
            break;

        case 5: //update all
            puts("update");
            update();
            break;
        case 6: //update id
            puts("update id");
            break;
        case 7: //select
            if (!ucitaj_sve(mat_dat,NULL,NULL))
               puts("ERROR: Greska pri citanju maticne datoteke.");

            break;
        case 8: //select id
            printf("Unesite id po kome pretrazujete: ");
            unsigned id2;
            scanf("%u",&id2);
            ocisti_bafer();
            if (!ucitaj_Id(mat_dat,id2))
                puts("ERROR: Greska pri citanju maticne datoteke.");
            break;
        default:
            puts("ERROR: Selektujte odgovarajucu opciju.");
            break;

    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pomoc_podmeni(int izbor) {
    trenutno = 1;
    switch (izbor) {
        case 0:
            stanje = glavni_meni;
            trenutno = 0;
            return;
        case 1: //o azuriranju
            ispis_azuriranje();
            break;
        case 2: //demo
            stanje = demo_podmeni;
            ocisti_ekran();
            menu_ispis(stanje);
            break;
        case 3: //o nama
            puts("Софтверски инжењер: Вукашин Живаљевић, vz20220281@student.fon.bg.ac.rs <остале информације>.");
            puts("Доменски инжењер : Саша Д. Лазаревић, <lazars@fon.bg.ac.rs> <остале информације>.");
            break;
        default:
            puts("ERROR: Selektujte odgovarajucu opciju.");
            break;

    }
}
void demo_podmeni_f(int izbor) {
    trenutno = 1;
    switch (izbor) {
        case 0:
            stanje = pomocni_meni;
            ocisti_ekran();
            menu_ispis(stanje);
            break;
        case 1:

            ucitaj(1);
            break;
        case 2:
            ucitaj(2);
            break;
        case 3:
            ucitaj(3);
            break;
        case 4:
            ucitaj(4);
            break;
        case 5:
            ucitaj(5);
            break;
        default:
            break;
    }

}

void menu(int a) {
    arg = a;
    stanje = glavni_meni;
    podesi_meni(arg);
    while (true) {
        if (trenutno == 0) {
            ocisti_ekran();
            menu_ispis(stanje);
        }int izbor;

        if (scanf("%d", &izbor) != 1) {
            puts("ERROR: Unesite broj.");
            ocisti_bafer();
            continue;
        }
        ocisti_bafer();

        switch (stanje) {
            case glavni_meni:
                switch (izbor) {
                    case 0:
                        return;
                    case 1:
                        stanje = transakcioni_meni;
                        continue;
                    case 2:
                        stanje = maticni_meni;
                        continue;
                    case 3:
                        stanje = pomocni_meni;
                        continue;
                    default:
                        puts("ERROR: Selektujte odgovarajuci meni.");
                        continue;
                }

            case transakcioni_meni:
                transakcioni_podmeni(izbor);
                break;

            case maticni_meni:
                maticni_podmeni(izbor);
                break;

            case pomocni_meni:
                pomoc_podmeni(izbor);
                break;
            case demo_podmeni:
                demo_podmeni_f(izbor);
                break;

        }
    }
}




