#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdd.h"
#include "cesar.h"
#include "scytale.h"
#include "vigenere.h"
#include "usefull.h"
#include "enigma.h"

#define SAISIE(x) fflush(stdin); scanf("%d",&x);

void menu()
{
    // initialiation des données
    int choice;

    // présentation du menu

    printf("Menu :  \n\n");
    printf("1 - Cesar\n");
    printf("2 - Scytale Spartiate\n");
    printf("3 - Chiffre de vigenere\n");
    printf("4 - Enigma\n\n");
    printf("5 - Quitter\n");

    // saisie
    s_scanf(&choice,1,5);

    // mise en place des sous-menus

    if(choice == 1) cesar();
    else if(choice == 2) scytale_menu();
    else if(choice == 3) vigenere();
    else if(choice == 4) enigma_menu();
    else if(choice == 5) exit(EXIT_SUCCESS);
}

int main()
{
    printf("\n\n\n\n\t\t\t\tEQUIPE \n\n");
    printf("\t\t\t\tLEBEGUE Sulian \n");
    printf("\t\t\t\tRAPILLY Thomas \n\n");
    printf("\t\t\t\tPROJET DE SDD\n\n\n\n\n\t\t");

    system("pause");
    system("cls");
    menu();

    return 0;
}
