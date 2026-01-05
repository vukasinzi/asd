#ifndef util_h
#define util_h

int kopiraj_datoteku(const char* odakle,const char* dokle);
bool sadrzi(TRANSAKCIJA *niz, unsigned id,int n);
bool sadrzi_p(PROIZVOD *niz, unsigned id,int n,int *pozicija);
void izbaci_element_t(TRANSAKCIJA **niz, int i,int *n);
#endif
