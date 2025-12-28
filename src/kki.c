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
            puts("create");
            break;
        case 2: //drop
            puts("drop");
            break;
        case 3: //insert
            puts("insert");
            break;
        case 4: //select
            puts("select");
            break;
        case 5: //select id
            puts("select id");
            break;
        default:
            puts("Selektujte odgovarajucu opciju.");
            break;

    }

}

void maticni_podmeni(int izbor) {
    trenutno = 1;
    switch (izbor) {
        case 0:
            stanje = glavni_meni;
            trenutno = 0;
            return;
        case 1: //create trans dat
            if (kreiraj_datoteku(mat_dat))
                puts("kreiran");
            break;
        case 2: //drop
            puts("drop");
            break;
        case 3: //insert
            puts("insert");
            break;
        case 4: //delete
            puts("delete");
            break;
        case 5: //update all
            puts("update");
            break;
        case 6: //update id
            puts("update id");
            break;
        case 7: //select
            puts("select");
            break;
        case 8: //select id
            puts("select id");
            break;
        default:
            puts("Selektujte odgovarajucu opciju.");
            break;

    }
}
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
        scanf("%d", &izbor);

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




