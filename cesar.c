

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "cesar.h"
#include "sdd.h"
#include "usefull.h"

#define CONTENT *node->content
#define P_CONTENT *(*p_l)->content
#define SAISIE(x) fflush(stdin); scanf("%d",&x);
#define S_GETS(x) fflush(stdin); gets(x);
#define DC(a,b) (a - b)
#define CC(a,b,c) (a+b-c) % 26 + c
#define CD(a,b,c) ((a-b-c) + 26) % 26 + c
#define RAND() rand() % 26

void cesar() {
    int choice;

    // Présentation

    printf("Le code cesar \n\n");
    printf("Menu\n\n");
    printf("1 - Chiffrage \n");
    printf("2 - Dechiffrage/Decryptage \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) cesar_cipher_menu();
    else if (choice == 2) cesar_decipher_menu();
}

void cesar_cipher_menu() {

    // initialisation des variables

    char str[400]; // la phrase à crypter
    list node = NULL; // la liste chainée
    int i, choice, key; // le compteur, le choix, la clé
    srand(time(NULL)); // préparation de la fonction random

    //  Présentation

    printf("Cryptage - Cesar : \n\n");
    printf("Veuillez saisir votre phrase a crypter : ");
    S_GETS(str);

    // Mise en place de la liste chainée

    for(i=0; i<strlen(str); i++) add_new_list(&node,&str[i],i);

    // Menu du choix de la clé

    printf("\n\n1 - Cle connue \n");
    printf("2 - Cle inconnue \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) {
        printf("Veuillez saisir votre cle (valeur entiere) : ");
        SAISIE(key); // clé saisie manuellement
        cesar_cipher(&node,&key); // Algo de chiffrage
    } else if(choice == 2) {
        key = RAND(); // clé random
        cesar_cipher(&node,&key); // Algo de chiffrage random
    }

    // On met la liste dans une chaine de caractère

    printf("Phrase cryptee : ");
    show_list(node);

    // La petite phrase d'avertissement

    printf("\n\nVeuillez notez votre phrase... \n");
    printf("\n");

    // Vidage de la mémoire
    free_list(&node);
}

/* Algo de chiffrage césar
 * Requiert une clé et une liste chainée
 */

void cesar_cipher(list *p_l,int *key) {
    list node = *p_l; // liste temporaire
    while(node) {
        if(CONTENT >= 'A' && CONTENT <= 'Z') // si le char est une majuscule
            CONTENT = CC(CONTENT,*key,'A'); // on chiffre la phrase
        else if(CONTENT >= 'a' && CONTENT <= 'z') // si le char est une minuscule
            CONTENT = CC(CONTENT,*key,'a'); // on chiffre la phrase
        node = node->next; // on avance dans la liste
    }
}

void cesar_cipher2(list *p_l,int *key,int *pos) {
    list node = *p_l; // liste temporaire
    int i;
    for(i=0;i<*pos;i++) node = node->next;
        if(CONTENT >= 'A' && CONTENT <= 'Z') // si le char est une majuscule
            CONTENT = CC(CONTENT,*key,'A'); // on chiffre la phrase
        else if(CONTENT >= 'a' && CONTENT <= 'z') // si le char est une minuscule
            CONTENT = CC(CONTENT,*key,'a'); // on chiffre la phrase
}

void cesar_decipher_menu() {

    // initialisation des variables

    char str[400]; // la phrase à crypter
    list node = NULL; // la liste chainée
    int i, choice, key; // le compteur, le choix, la clé
    srand(time(NULL)); // préparation de la fonction random

    //  Présentation

    printf("decryptage - Cesar : \n\n");
    printf("Veuillez saisir votre phrase a decrypter : ");
    S_GETS(str);

    // Mise en place de la liste chainée

    for(i=0; i<strlen(str); i++) add_new_list(&node,&str[i],i);

    // Menu du choix de la clé

    printf("\n\n1 - Cle connue \n");
    printf("2 - Cle inconnue \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) {
        printf("Veuillez saisir votre cle (valeur entiere) : ");
        SAISIE(key); // clé saisie manuellement
        cesar_decipher(&node,&key); // Algo de chiffrage
    } else if(choice == 2) {
        cesar_decrypter(&node);
    }

    // On met la liste dans une chaine de caractère

    printf("Phrase decryptee : ");
    show_list(node);

    // La petite phrase d'avertissement

    printf("\n\nVeuillez notez votre phrase... \n");
    printf("\n");

    // Vidage de la mémoire
    free_list(&node);
}

/* Algo de déchiffrage césar
 * Requiert une clé et une liste chainée
 */

void cesar_decipher(list *p_l,int *key) {
    list node = *p_l; // liste temporaire
    while(node) {
        if(CONTENT >= 'A' && CONTENT <= 'Z') // si le char est une majuscule
            CONTENT = CD(CONTENT,*key,'A'); // on déchiffre la phrase chiffrée
        else if(CONTENT >= 'a' && CONTENT <= 'z') // si le char est une minuscule
            CONTENT = CD(CONTENT,*key,'a'); // on déchiffre la phrase chiffrée
        node = node->next; // on avance dans la liste
    }
}


void cesar_decrypter(list *p_l) {
    int i,j = length2(*p_l),k;
    list node = *p_l;

    double tab[26] = {
        7.636, 0.901, 3.260, 3.669, 14.715, 1.006,
        0.866, 0.737, 7.529, 0.545, 0.049, 5.456,
        2.968, 7.095, 5.378, 3.021, 1.362, 6.653,
        7.948, 7.244, 6.311, 1.628, 0.144, 0.387,
        0.308, 0.136
    };
    double crypt[26];
    double diff[26], moy = 0;

    // Mise en plage de l'analyse fréquentielle
    for(i = 0; i < 26; i++) crypt[i] = 0;
    // Tri des structures d'analyses fréquentielles

    int decalage = 0;
    double min = 0;

    // Analyse fréquentielle
    for( i = 1; i < 26 ; i++ ) {

        cesar_decipher(&node,&i);

        k = 0;
        while(k<j) {
            if(*node->content >= 'A' && *node->content <= 'Z') // si le char est une majuscule
               {
                   crypt[*node->content - 'A'] += 1; k++; // on déchiffre la phrase chiffrée
               }
            else if(*node->content >= 'a' && *node->content <= 'z') // si le char est une minuscule
                {
                    crypt[*node->content - 'a'] += 1; k++; // on déchiffre la phrase chiffrée
                }
            node = node->next;
        }

        node = *p_l;
        cesar_cipher(&node,&i);

        for(k=0; k<26; k++) {
            crypt[k] = (crypt[k] *100)/j;
            diff[k] = crypt[k] - tab[k];
            if(diff[k] < 0) diff[k] *= -1;
            moy += diff[k];
            moy /= j;
        }

        if(i == 1 || moy < min ) {
            decalage = i;
            min = moy;
        }

        for(k = 0; k < 26; k++) crypt[k] = 0;
    }

    cesar_decipher(&node,&decalage);

}
