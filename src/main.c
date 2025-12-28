
#include "kki.h"
#include "misc.h"
#include  "datoteka.h"
void podesavanje() {
    kreiraj_foldere();
    char dat[7];
    datum(dat);
    podesi_pathove(dat);
}
int main()
{
    podesavanje();
    menu();
    return 0;
}
