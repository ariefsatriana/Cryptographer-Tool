#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usefull.h"

#define SAISIE(x) fflush(stdin); secure = scanf("%d",x);

void s_scanf(int *choice,int a,int b) {
    if(!choice) return;
    int ready = 1;
    int secure = 0;
    int fail = 0;

    do {
        if(fail) {
            printf("\nAttention erreur ! \n");
            printf("Mauvaise saisie ! \n");
            printf("Veuillez resaisir \n");
            fail = 0;
        }
        printf("Votre choix : ");
        SAISIE(choice);
        if( (*choice >= a && *choice <= b) && secure == 1 ) ready--;
        else fail = 1;
    } while(ready);
    system("cls");
}

alphabet prepare_alphabet(alphabet *a) {
    int i = 0;
    for(i = 0; i < 26; i++) {
        a[i].letter = 'a' + 0;
        a[i].frequency = 0;
    }
    return *a;
}
