#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sdd.h"
#include "usefull.h"
#include "vigenere.h"
#include "cesar.h"

#define CONTENT *node->content
#define P_CONTENT *(*p_l)->content
#define SAISIE(x) fflush(stdin); scanf("%d",&x);
#define S_GETS(x) fflush(stdin); gets(x);
#define DC(a,b) (a - b)
#define CC(a,b,c) (a+b-c) % 26 + c
#define CD(a,b,c) ((a-b-c) + 26) % 26 + c
#define RAND() rand() % 26

void vigenere() {
    int choice;

    // Présentation

    printf("Le chiffre de vigenere \n\n");
    printf("Menu\n\n");
    printf("1 - Chiffrage \n");
    printf("2 - Dechiffrage/Decryptage \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) vigenere_cipher_menu();
    else if (choice == 2) vigenere_decipher_menu();
}

void vigenere_cipher_menu() {

    // initialisation des variables

    char str[400]; // la phrase à crypter
    char key[400];
    list node = NULL; // la liste chainée
    int i, choice; // le compteur, le choix, la clé

    //  Présentation

    printf("Cryptage - vigenere : \n\n");
    printf("Veuillez saisir votre phrase a crypter : ");
    S_GETS(str);

    // Mise en place de la liste chainée

    for(i=0; i<strlen(str); i++) add_new_list(&node,&str[i],i);

    // Menu du choix de la clé

    printf("\n\n1 - Cle connue \n");
    printf("2 - Cle inconnue \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) {
        printf("Veuillez saisir votre cle : ");
        S_GETS(key);
        vigenere_cipher(&node,key); // Algo de chiffrage
    } else if(choice == 2) {
        // key = RAND(); // clé random
        // vigenere_cipher(&node,&key); // Algo de chiffrage random
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

void vigenere_decipher_menu() {

    // initialisation des variables

    char str[1000]; // la phrase à crypter
    char key[400];
    list node = NULL; // la liste chainée
    int i, choice; // le compteur, le choix, la clé
    srand(time(NULL)); // préparation de la fonction random

    //  Présentation

    printf("decryptage - vigenere : \n\n");
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
        S_GETS(key);
        vigenere_decipher(&node,key); // Algo de chiffrage
    } else if(choice == 2) {
        vigenere_decrypter(&node,str);
        return;
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


void vigenere_cipher(list* p_l,char* key) {
    list node = *p_l;
    int l = strlen(key);
    int i = 0, j = 0;

    while(node) {
        if ( i == l ) i = 0;
        if(key[i] >= 'a' && key[i] <= 'z') j = key[i] - 'a';
        else if (key[i] >= 'A' && key[i] <= 'Z') j = key[i] - 'A';
        if(*node->content >= 'a' && *node->content <= 'z') {
            *node->content = (*node->content - 'a' + j ) % 26 + 'a';
            i++;
        } else if(*node->content >= 'A' && *node->content <= 'Z') {
            *node->content = (*node->content - 'A' + j ) % 26 + 'A';
            i++;
        }
        node = node->next;
    }
}

void vigenere_decipher(list* p_l,char* key) {
    list node = *p_l;
    int l = strlen(key);
    int i = 0, j = 0;

    while(node) {
        if ( i == l ) i = 0;
        if(key[i] >= 'a' && key[i] <= 'z') j = key[i] - 'a';
        else if (key[i] >= 'A' && key[i] <= 'Z') j = key[i] - 'A';
        if(*node->content >= 'a' && *node->content <= 'z') {
            *node->content = (*node->content - 'a' - j + 26 ) % 26 + 'a';
            i++;
        } else if(*node->content >= 'A' && *node->content <= 'Z') {
            *node->content = (*node->content - 'A' - j + 26 ) % 26 + 'A';
            i++;
        }
        node = node->next;
    }
}


double indice(double l,double n) {
    return ((l*l-l)/(n*(n-1.0)));
}

void vigenere_decrypter(list *p_l,char *str) {
    int i,j = length2(*p_l),k;
    int test = 0;
    list node = *p_l;
    double crypt[26];
    char key[400];
    double diff[26], moy = 0;
    double min = 0;
    int decalage2 = 0;

    double tab[26] = {
        7.636, 0.901, 3.260, 3.669, 14.715, 1.006,
        0.866, 0.737, 7.529, 0.545, 0.049, 5.456,
        2.968, 7.095, 5.378, 3.021, 1.362, 6.653,
        7.948, 7.244, 6.311, 1.628, 0.144, 0.387,
        0.308, 0.136
    };

    // Mise en plage de l'analyse fréquentielle
    for(i = 0; i < 26; i++) crypt[i] = 0;
    // Tri des structures d'analyses fréquentielles

    int decalage = 0;
    double longueur = 0;
    // Analyse fréquentielle
    i = 1;
    int l;

    while(i < 26) {
        k = 0;
        longueur = 0;
        while(k < j) {
            if(*node->content >= 'A' && *node->content <= 'Z') { // si le char est une majuscule
                crypt[*node->content - 'A'] += 1;
                k++; // on déchiffre la phrase chiffrée
            } else if(*node->content >= 'a' && *node->content <= 'z') { // si le char est une minuscule
                crypt[*node->content - 'a'] += 1;
                k++; // on déchiffre la phrase chiffrée
            }
            if(k == k+i-1) {
                node = node->next;
                longueur++;
            } else {
                for(l = k; l < k+i ; l++) {
                    if(!node->next);
                    else node = node->next;
                }
                k = l;
                longueur++;
            }

        }
        node = *p_l;


        double IC = 0;
        for(l = 1 ; l < 26 ; l++) IC += indice((double) crypt[l],longueur);
        printf("%lf\n",IC);
        for(l = 0; l < 26; l++) crypt[l] = 0;
        if(IC > 0.06) {
            decalage = i;
            i = 26;
        }
        i++;
    }

    printf("decalage : %d\n",decalage);

    do {


    for( i = 1; i < 26 ; i++ ) {

        for ( k = 0 ; k < j ; k++) {
            for ( l = 0 ; l < j/decalage ; l++ ) {
                if( k + l*decalage % decalage == 0 ) {
                    if(str[k] >= 'A' && str[k] <= 'Z') // si le char est une majuscule
                        str[k] = CD(str[k],i,'A'); // on déchiffre la phrase chiffrée
                    else if(str[i] >= 'a' && str[k] <= 'z') // si le char est une minuscule
                        str[k] = CD(str[k],i,'a'); // on déchiffre la phrase chiffrée
                }
            }
        }



        k = 0;
        while(k<j) {
            if(str[i] >= 'A' && str[i] <= 'Z') { // si le char est une majuscule
                crypt[str[i] - 'A'] += 1;
            } else if(str[i] >= 'a' && str[i] <= 'z') { // si le char est une minuscule
                crypt[str[i] - 'a'] += 1;
            }
            k++;
        }
        node = *p_l;

        for ( k = 0 ; k < j ; k++) {
            for ( l = 0 ; l < j/decalage ; l++ ) {
                if( k + l*decalage % decalage == 0 ) {
                    if(str[k] >= 'A' && str[k] <= 'Z') // si le char est une majuscule
                        str[k] = CC(str[k],i,'A'); // on déchiffre la phrase chiffrée
                    else if(str[k] >= 'a' && str[k] <= 'z') // si le char est une minuscule
                        str[k] = CC(str[k],i,'a'); // on déchiffre la phrase chiffrée
                }
            }
        }

        for(k=0; k<26; k++) {
            crypt[k] = (crypt[k] *100)/j;
            diff[k] = crypt[k] - tab[k];
            if(diff[k] < 0) diff[k] *= -1;
            moy += diff[k];
            moy /= j;
        }

        if(i == 1 || moy < min ) {
            decalage2 = i;
            min = moy;
        }

        for(k = 0; k < 26; k++) crypt[k] = 0;
    }

        key[test] = 'a' + decalage2;
        test++;

    }
    while(test < decalage);

    puts(key);

}


