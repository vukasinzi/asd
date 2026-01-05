#include <stdio.h>
#include <stdlib.h>
#include <defs.h>
#include <stdbool.h>
int kopiraj_datoteku(const char* odakle, const char* dokle)
{
        char cmd[1024];
    #ifdef _WIN32
            snprintf(cmd, sizeof cmd,
                     "cmd /C copy /Y \"%s\" \"%s\" >NUL",
                     odakle, dokle);
    #else
            snprintf(cmd, sizeof cmd,
                     "cp -f -- \"%s\" \"%s\"",
                     odakle, dokle);
    #endif
        return system(cmd);
}
bool sadrzi(const TRANSAKCIJA *niz, unsigned id,int n) {
    for (int i = 0; i < n;i++) {
        if (niz[i].Id == id)
            return true;
    }
    return false;
}
