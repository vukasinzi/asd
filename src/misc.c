#include <stdlib.h>
#include "misc.h"
void ocisti_ekran() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

