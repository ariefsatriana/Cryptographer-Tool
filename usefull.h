#ifndef USEFULL_H_INCLUDED
#define USEFULL_H_INCLUDED

#include "sdd.h"

typedef struct alphabet {
    int letter;
    double frequency;
} alphabet;

void s_scanf(int *choice,int a,int b);
alphabet prepare_alphabet(alphabet *a);

#endif // USEFULL_H_INCLUDED
