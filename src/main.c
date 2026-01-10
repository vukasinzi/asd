#include "misc.h"
#include "kki.h"


int main(int argc, char *argv[])
{
    podesavanje();
    menu(parsiraj_argumente(argc,argv));
    return 0;
}
