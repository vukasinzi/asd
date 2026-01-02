#include <stdio.h>
#include "kki.h"

#include <stdbool.h>
#include "datoteka.h"
#include "defs.h"
#include "misc.h"

int trenutno = 0;
void menu_ispis(const Menu m)
{
    switch (m) {
        case glavni_meni:
            ocisti_ekran();
            puts("************************************************************");
            puts("* Aplikacija: ASD *");
            puts("* Opis: Azuriranje serijske (sortirane redne) datoteke *");
            puts("* Verzija: 1.0 *");
            puts("* Upotreba: asd.exe [-d[1|2|3|4|5]] *");
            puts("* 1 - demo za prvi slucaj azuriranja *");
            puts("* 2 - demo za drugi slucaj azuriranja *");
            puts("* Datum: dd.mm.2022. *");
            puts("* Autor: Vukašin Živaljević vz20220281@student.fon.bg.ac.rs *");
            puts("* Autor: Lazar Stojanović ls20220164@student.fon.bg.ac.rs *");
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

            puts("MENI Pomoc");
            puts("==================================");
            puts("0. Povratak");
            puts("1. O azuriranju serijske datoteke");
            puts("2. Demo");
            puts("3. O nama");

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
            if (kreiraj_datoteku(tran_dat))
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
            if (!ucitaj_sve_tran(tran_dat))
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
            puts("Selektujte odgovarajucu opciju.");
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
            if (kreiraj_datoteku(mat_dat))
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
            ocisti_bafer();
            printf("Unesite naziv proizvoda: ");
            if (scanf("%14s",p.Naziv)!= 1)
            {
                ocisti_bafer();
                puts("ERROR: Pogresan format. akcija se obustavlja.");
                break;
            }
            ocisti_bafer();
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
            break;
        case 6: //update id
            puts("update id");
            break;
        case 7: //select
            if (!ucitaj_sve(mat_dat))
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
            puts("Selektujte odgovarajucu opciju.");
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
            puts("o azuriranju");
            break;
        case 2: //demo
            puts("demo");
            break;
        case 3: //o nama
            puts("o nama");
            break;
        default:
            puts("Selektujte odgovarajucu opciju.");
            break;

    }
}


void menu() {

    stanje = glavni_meni;
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
                        puts("Selektujte odgovarajuci meni.");
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
        }
    }
}




