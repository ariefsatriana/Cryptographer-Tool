#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sdd.h"
#include "cesar.h"
#include "scytale.h"
#include "vigenere.h"
#include "usefull.h"
#include "enigma.h"

#define SAISIE(x) fflush(stdin); scanf("%d",&x);
#define S_GETS(x) fflush(stdin); gets(x);
#define RAND() rand() % 21




void scytale_menu() {
    int choice;

    // Présentation

    printf("La scytale spartiate \n\n");
    printf("Menu\n\n");
    printf("1 - Chiffrage \n");
    printf("2 - Dechiffrage/Decryptage \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) scytale_cipher_menu();
    else if (choice == 2) scytale_decipher_menu();
}

void scytale_cipher_menu() {

    // initialisation des variables

    char str[400]; // la phrase à crypter
    list node = NULL; // la liste chainée
    list new_node = NULL;
    int i, choice, key; // le compteur, le choix, la clé
    srand(time(NULL)); // préparation de la fonction random

    //  Présentation

    printf("Cryptage - Scytale : \n\n");
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
        new_node = scytale_cipher(&node,&key); // Algo de chiffrage
    } else if(choice == 2) {
        key = RAND(); // clé random
        new_node = scytale_cipher(&node,&key); // Algo de chiffrage random
    }

    // On met la liste dans une chaine de caractère

    printf("Phrase cryptee : ");
    show_list(new_node);

    // La petite phrase d'avertissement

    printf("\n\nVeuillez notez votre phrase... \n");
    printf("\n");

    // Vidage de la mémoire
    free_list(&node);
    free_list(&new_node);
}

/* Algo de chiffrage césar
 * Requiert une clé et une liste chainée
 */

void scytale_decipher_menu() {

    // initialisation des variables

    char str[400]; // la phrase à crypter
    list node = NULL; // la liste chainée
    list new_node = NULL;
    int i, choice, key = 0; // le compteur, le choix, la clé

    //  Présentation

    printf("decryptage - Scytale : \n\n");
    printf("Veuillez saisir votre phrase a decrypter : ");
    S_GETS(str);

    // Mise en place de la liste chainée

    for(i=0; i<strlen(str); i++) add_new_list(&node,&str[i],i);

    show_list(node); printf("\n");
    // Menu du choix de la clé

    printf("\n\n1 - Cle connue \n");
    printf("2 - Cle inconnue \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) {
        printf("Veuillez saisir votre cle (valeur entiere) : ");
        SAISIE(key); // clé saisie manuellement
        new_node = scytale_decipher(&node,&key); // Algo de dechiffrage
    } else if(choice == 2) {
        scytale_decrypter(&node);
        return;
    }

    // On met la liste dans une chaine de caractère

    printf("Phrase decryptee : ");
    show_list(new_node);

    // La petite phrase d'avertissement

    printf("\n\nVeuillez notez votre phrase... \n");
    printf("\n");

    // Vidage de la mémoire
    free_list(&node);
    free_list(&new_node);
}

/* Algo de déchiffrage césar
 * Requiert une clé et une liste chainée
 */

list scytale_cipher(list *p_l,int *value) {
    char **tab;
    list node = *p_l;
    double v = (double) length(*p_l)/ (double) (*value);
    printf("%d",length(*p_l));
    printf("\n");
    printf("%lf",v);
    printf("\n");
    int diametre = v;
    int i,j,k=0;

    show_list(node);
    printf("\n");

    if(v != diametre) diametre = diametre+1;
    printf("%d",diametre);
    printf("\n");

    tab = (char**) malloc(*value * sizeof(char*));

    for (i = 0 ; i < *value ; i++)
        tab[i] =  malloc( diametre * sizeof(char));

    for(i = 0 ; i < *value ; i++) {
        for (j = 0; j < diametre ; j++) {
            if(!node) tab[i][j] = ' ';
            else {
            tab[i][j] = *node->content;
            node = node->next;
            }
        }
    }

    list new_node = NULL;
    for(i = 0 ; i < diametre ; i++) {
        for (j = 0; j < *value ; j++) {
            add_new_list(&new_node,&tab[j][i],k);
            k++;
        }
    }
    show_list(new_node);
    printf("\n");
    return new_node;
}

list scytale_decipher(list *p_l,int *value) {
    char **tab;
    list node = *p_l;
    double v = (double) length(*p_l) / (double) (*value);
    int diametre = v;
    int i,j,k=0;

    if(v != diametre) diametre = diametre+1;

    tab = (char**) malloc( *value * sizeof(char*));

    for (i = 0 ; i < *value ; i++)
        tab[i] =  malloc( diametre * sizeof(char));

    for(j = 0 ; j < diametre ; j++) {
        for (i = 0; i < *value ; i++) {
            if(!node) tab[i][j] = ' ';
            else {
            tab[i][j] = *node->content;
            node = node->next;
            }
        }
    }

    list new_node = NULL;
    for(i = 0 ; i < *value ; i++) {
        for (j = 0; j < diametre ; j++) {
            add_new_list(&new_node,&tab[i][j],k);
            k++;
        }
    }
    return new_node;
}


void add_new_scytale(scytale *p_l,int position,int hauteur,int diametre) {
    scytale node = (scytale) malloc(sizeof(scytaleNode));
    node->tab.hauteur = hauteur;
    node->tab.diametre = diametre;

    if (!*p_l || !position) {
        *p_l = node;
        node->next = NULL;
        node->prev = NULL;
        return;
    }
    scytale oldList = *p_l;

    while (oldList->next) oldList = oldList->next;

    node->next = oldList->next;
    node->prev = oldList;
    oldList->next = node;
}


void scytale_decrypter(list *p_l){

    bigramme base[550];

    base[0].big[0] = 'E';
    base[0].big[1] = 'S';
    base[0].frequency = 32207;
    base[1].big[0] = 'O';
    base[0].big[1] = 'U';
    base[1].frequency = 12074;
    base[2].big[0] = 'C';
    base[0].big[1] = 'E';
    base[2].frequency = 8502;
    base[3].big[0] = 'T';
    base[0].big[1] = 'R';
    base[3].frequency = 6871;
    base[4].big[0] = 'M';
    base[0].big[1] = 'A';
    base[4].frequency = 5208;
    base[5].big[0] = 'T';
    base[0].big[1] = 'D';
    base[5].frequency = 4689;
    base[6].big[0] = 'D';
    base[0].big[1] = 'I';
    base[6].frequency = 3800;
    base[7].big[0] = 'N';
    base[0].big[1] = 'I';
    base[7].frequency = 3182;
    base[8].big[0] = 'E';
    base[0].big[1] = 'I';
    base[8].frequency = 2497;
    base[9].big[0] = 'I';
    base[0].big[1] = 'Q';
    base[9].frequency = 2162;
    base[10].big[0] = 'O';
    base[0].big[1] = 'S';
    base[10].frequency = 1792;
    base[11].big[0] = 'N';
    base[0].big[1] = 'P';
    base[11].frequency = 1487;
    base[12].big[0] = 'S';
    base[0].big[1] = 'R';
    base[12].frequency = 1247;
    base[13].big[0] = 'I';
    base[0].big[1] = 'F';
    base[13].frequency = 1148;
    base[14].big[0] = 'N';
    base[0].big[1] = 'L';
    base[14].frequency = 983;
    base[15].big[0] = 'P';
    base[0].big[1] = 'T';
    base[15].frequency = 706;
    base[16].big[0] = 'C';
    base[0].big[1] = 'C';
    base[16].frequency = 620;
    base[17].big[0] = 'T';
    base[0].big[1] = 'F';
    base[17].frequency = 509;
    base[18].big[0] = 'L';
    base[0].big[1] = 'Y';
    base[18].frequency = 432;
    base[19].big[0] = 'R';
    base[0].big[1] = 'B';
    base[19].frequency = 365;
    base[20].big[0] = 'A';
    base[0].big[1] = 'H';
    base[20].frequency = 256;
    base[21].big[0] = 'Z';
    base[0].big[1] = 'E';
    base[21].frequency = 201;
    base[22].big[0] = 'L';
    base[0].big[1] = 'R';
    base[22].frequency = 164;
    base[23].big[0] = 'Z';
    base[0].big[1] = 'L';
    base[23].frequency = 123;
    base[24].big[0] = 'L';
    base[0].big[1] = 'E';
    base[24].frequency = 22833;
    base[25].big[0] = 'A';
    base[0].big[1] = 'L';
    base[25].frequency = 11858;
    base[26].big[0] = 'N';
    base[0].big[1] = 'S';
    base[26].frequency = 8501;
    base[27].big[0] = 'N';
    base[0].big[1] = 'D';
    base[27].frequency = 6632;
    base[28].big[0] = 'L';
    base[0].big[1] = 'L';
    base[28].frequency = 5167;
    base[29].big[0] = 'S';
    base[0].big[1] = 'P';
    base[29].frequency = 4536;
    base[30].big[0] = 'R';
    base[0].big[1] = 'T';
    base[30].frequency = 3625;
    base[31].big[0] = 'A';
    base[0].big[1] = 'M';
    base[31].frequency = 3041;
    base[32].big[0] = 'T';
    base[0].big[1] = 'P';
    base[32].frequency = 2483;
    base[33].big[0] = 'E';
    base[0].big[1] = 'G';
    base[33].frequency = 2104;
    base[34].big[0] = 'R';
    base[0].big[1] = 'R';
    base[34].frequency = 1756;
    base[35].big[0] = 'I';
    base[0].big[1] = 'G';
    base[35].frequency = 1425;
    base[36].big[0] = 'E';
    base[0].big[1] = 'O';
    base[36].frequency = 1244;
    base[37].big[0] = 'P';
    base[0].big[1] = 'P';
    base[37].frequency = 1145;
    base[38].big[0] = 'N';
    base[0].big[1] = 'U';
    base[38].frequency = 909;
    base[39].big[0] = 'S';
    base[0].big[1] = 'B';
    base[39].frequency = 706;
    base[40].big[0] = 'R';
    base[0].big[1] = 'V';
    base[40].frequency = 600;
    base[41].big[0] = 'T';
    base[0].big[1] = 'N';
    base[41].frequency = 496;
    base[42].big[0] = 'U';
    base[0].big[1] = 'O';
    base[42].frequency = 421;
    base[43].big[0] = 'U';
    base[0].big[1] = 'F';
    base[43].frequency = 364;
    base[44].big[0] = 'U';
    base[0].big[1] = 'U';
    base[44].frequency = 255;
    base[45].big[0] = 'Y';
    base[0].big[1] = 'C';
    base[45].frequency = 197;
    base[46].big[0] = 'U';
    base[0].big[1] = 'Q';
    base[46].frequency = 163;
    base[47].big[0] = 'M';
    base[0].big[1] = 'D';
    base[47].frequency = 119;
    base[48].big[0] = 'R';
    base[0].big[1] = 'E';
    base[48].frequency = 21480;
    base[50].big[0] = 'N';
    base[0].big[1] = 'E';
    base[50].frequency = 11635;
    base[51].big[0] = 'R';
    base[0].big[1] = 'A';
    base[51].frequency = 8368;
    base[52].big[0] = 'U';
    base[0].big[1] = 'N';
    base[52].frequency = 6351;
    base[53].big[0] = 'U';
    base[0].big[1] = 'T';
    base[53].frequency = 5140;
    base[54].big[0] = 'S';
    base[0].big[1] = 'L';
    base[54].frequency = 4508;
    base[55].big[0] = 'A';
    base[0].big[1] = 'P';
    base[55].frequency = 3626;
    base[56].big[0] = 'H';
    base[0].big[1] = 'E';
    base[56].frequency = 3022;
    base[57].big[0] = 'T';
    base[0].big[1] = 'U';
    base[57].frequency = 2464;
    base[58].big[0] = 'I';
    base[0].big[1] = 'M';
    base[58].frequency = 2102;
    base[59].big[0] = 'T';
    base[0].big[1] = 'C';
    base[59].frequency = 1755;
    base[60].big[0] = 'E';
    base[0].big[1] = 'X';
    base[60].frequency = 1414;
    base[61].big[0] = 'N';
    base[0].big[1] = 'F';
    base[61].frequency = 1240;
    base[62].big[0] = 'G';
    base[0].big[1] = 'A';
    base[62].frequency = 1133;
    base[63].big[0] = 'G';
    base[0].big[1] = 'U';
    base[63].frequency = 896;
    base[64].big[0] = 'S';
    base[0].big[1] = 'J';
    base[65].frequency = 705;
    base[65].big[0] = 'E';
    base[0].big[1] = 'H';
    base[66].frequency = 584;
    base[67].big[0] = 'O';
    base[0].big[1] = 'Y';
    base[67].frequency = 491;
    base[68].big[0] = 'H';
    base[0].big[1] = 'U';
    base[68].frequency = 418;
    base[69].big[0] = 'T';
    base[0].big[1] = 'B';
    base[69].frequency = 360;
    base[70].big[0] = 'N';
    base[0].big[1] = 'H';
    base[70].frequency = 248;
    base[71].big[0] = 'X';
    base[0].big[1] = 'Q';
    base[71].frequency = 192;
    base[72].big[0] = 'D';
    base[0].big[1] = 'M';
    base[72].frequency = 161;
    base[73].big[0] = 'O';
    base[0].big[1] = 'A';
    base[73].frequency = 118;
    base[74].big[0] = 'D';
    base[0].big[1] = 'E';
    base[74].frequency = 21388;
    base[75].big[0] = 'Q';
    base[0].big[1] = 'U';
    base[75].frequency = 11360;
    base[76].big[0] = 'I';
    base[0].big[1] = 'N';
    base[76].frequency = 8326;
    base[77].big[0] = 'A';
    base[0].big[1] = 'L';
    base[77].frequency = 6339;
    base[78].big[0] = 'V';
    base[0].big[1] = 'E';
    base[78].frequency = 5059;
    base[79].big[0] = 'A';
    base[0].big[1] = 'S';
    base[79].frequency = 4407;
    base[80].big[0] = 'T';
    base[0].big[1] = 'L';
    base[80].frequency = 3608;
    base[81].big[0] = 'M';
    base[0].big[1] = 'P';
    base[81].frequency = 2446;
    base[82].big[0] = 'I';
    base[0].big[1] = 'D';
    base[82].frequency = 2053;
    base[83].big[0] = 'C';
    base[0].big[1] = 'T';
    base[83].frequency = 1749;
    base[84].big[0] = 'C';
    base[0].big[1] = 'R';
    base[84].frequency = 1408;
    base[85].big[0] = 'F';
    base[0].big[1] = 'R';
    base[85].frequency = 1237;
    base[86].big[0] = 'M';
    base[0].big[1] = 'B';
    base[86].frequency = 1132;
    base[87].big[0] = 'T';
    base[0].big[1] = 'M';
    base[87].frequency = 876;
    base[88].big[0] = 'O';
    base[0].big[1] = 'G';
    base[88].frequency = 694;
    base[89].big[0] = 'J';
    base[0].big[1] = 'U';
    base[89].frequency = 577;
    base[90].big[0] = 'L';
    base[0].big[1] = 'Y';
    base[90].frequency = 485;
    base[91].big[0] = 'T';
    base[0].big[1] = 'V';
    base[91].frequency = 416;
    base[92].big[0] = 'O';
    base[0].big[1] = 'F';
    base[92].frequency = 347;
    base[93].big[0] = 'O';
    base[0].big[1] = 'Q';
    base[93].frequency = 241;
    base[94].big[0] = 'T';
    base[0].big[1] = 'G';
    base[94].frequency = 191;
    base[95].big[0] = 'X';
    base[0].big[1] = 'L';
    base[95].frequency = 161;
    base[96].big[0] = 'Z';
    base[0].big[1] = 'V';
    base[96].frequency = 116;
    base[97].big[0] = 'E';
    base[0].big[1] = 'N';
    base[97].frequency = 21109;
    base[98].big[0] = 'M';
    base[0].big[1] = 'E';
    base[98].frequency = 10573;
    base[99].big[0] = 'E';
    base[0].big[1] = 'U';
    base[99].frequency = 8277;
    base[100].big[0] = 'A';
    base[0].big[1] = 'U';
    base[100].frequency = 6284;
    base[101].big[0] = 'L';
    base[0].big[1] = 'I';
    base[101].frequency = 5001;
    base[102].big[0] = 'N';
    base[0].big[1] = 'A';
    base[102].frequency = 4388;
    base[103].big[0] = 'S';
    base[0].big[1] = 'U';
    base[103].frequency = 3582;

    int i = 103;
    int j = 103;

    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 2781;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 2384;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 2052;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 1710;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 1380;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 1218;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 1124;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 860;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 687;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 575;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 480;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 402;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 332;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 239;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 190;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 156;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 113;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 16435;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 10226;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 7943;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 6274;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 4989;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 4363;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 3478;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 2730;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 2350;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 2009;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 1697;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 1678;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 1214;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 1116;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 822;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 679;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 822;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 679;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 573;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 474;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 399;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 320;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 234;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 181;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 156;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 111;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 16265;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 10082;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 7896;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 6230;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 4969;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 4363;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 3478;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 2730;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 2350;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 2009;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 1697;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 1378;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 1214;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 1116;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 822;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 679;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 573;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 474;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 399;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 320;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 234;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 181;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 146;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 105;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 15678;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 9867;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 7563;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 5966;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 4923;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 4009;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 3326;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 2661;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 2307;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 1955;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 1576;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 1355;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 1182;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 1096;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 775;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 651;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 538;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 452;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 384;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 286;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 215;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 179;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 143;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 98;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 14510;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 9852;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 7453;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 5907;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 4910;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 3883;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 3299;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 2658;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 2302;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 1918;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 1574;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 1349;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 1181;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 1084;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 765;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 643;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 535;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 451;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 379;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 285;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 214;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 172;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 142;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 97;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 13824;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 9611;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 7407;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 5897;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 4891;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 3861;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 3275;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 2657;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 2257;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 1872;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 1530;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 1301;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 1178;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 1067;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 758;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 643;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 520;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 445;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 377;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 280;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 207;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 172;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 142;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 97;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 12694;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 9004;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 7035;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 5753;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 4845;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 3816;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 3257;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 2633;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 2215;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 1834;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 1516;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 1255;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 1163;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 1035;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 741;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 633;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 516;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 436;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 373;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 274;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 203;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 168;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 127;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 95;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 12195;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 8792;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 6944;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 5665;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 4813;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 3801;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 3239;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 2196;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 1792;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 1487;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 1252;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 1151;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 989;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 731;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 624;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 433;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 368;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 272;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 202;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 168;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 126;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 92;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 92;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 74;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 60;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 54;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 45;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 31;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 26;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 20;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 16;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 14;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 7;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 90;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 70;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 59;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 54;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 44;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 34;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 26;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 19;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 16;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 13;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 7;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 88;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 69;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 58;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 53;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 43;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 33;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 25;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 19;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 16;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 13;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 7;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 88;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 69;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 58;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 53;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 42;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 32;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 24;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 19;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 16;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 13;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 7;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 88;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 66;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 57;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 53;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 39;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 31;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 23;
    i++; base[i].big[0]  = 'S';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 19;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 15;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 13;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 11;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 7;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 86;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 65;
    i++; base[i].big[0]  = 'E';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 57;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 53;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 39;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 30;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 23;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 19;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 15;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'U';
    j++; base[j].frequency = 13;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 11;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 7;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 82;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 65;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 57;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 53;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 38;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 30;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 22;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 18;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 15;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 13;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 11;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 85;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 65;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 56;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 53;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 38;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 30;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 22;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = "MI";
    j++; base[j].frequency = 18;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 15;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 13;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 11;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'L';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 78;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 64;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 55;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 52;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 38;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 29;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 21;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 18;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 15;
    i++; base[i].big[0]  = 'A';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 10;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 46;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 62;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 55;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 48;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'E';
    j++; base[j].frequency = 37;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 27;
    i++; base[i].big[0]  = 'R';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 21;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 17;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 15;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'F';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'J';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'Y';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 76;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 60;
    i++; base[i].big[0]  = 'N';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 55;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 46;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 37;
    i++; base[i].big[0]  = 'I';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 27;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 20;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'A';
    j++; base[j].frequency = 17;
    i++; base[i].big[0]  = 'C';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 14;
    i++; base[i].big[0]  = 'G';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 9;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 8;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'T';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'X';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 75;
    i++; base[i].big[0]  = 'D';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 60;
    i++; base[i].big[0]  = 'Y';
    base[i].big[1]  = 'G';
    j++; base[j].frequency = 55;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'B';
    j++; base[j].frequency = 46;
     i++; base[i].big[0]  = 'X';
     base[i].big[1]  = 'U';
    j++; base[j].frequency = 37;
     i++; base[i].big[0]  = 'B';
     base[i].big[1]  = 'B';
    j++; base[j].frequency = 26;
     i++; base[i].big[0]  = 'L';
     base[i].big[1]  = 'K';
    j++; base[j].frequency = 20;
     i++; base[i].big[0]  = 'X';
     base[i].big[1]  = 'Y';
    j++; base[j].frequency = 17;
     i++; base[i].big[0]  = 'F';
     base[i].big[1]  = 'G';
    j++; base[j].frequency = 14;
     i++; base[i].big[0]  = 'I';
     base[i].big[1]  = 'Y';
    j++; base[j].frequency = 12;
     i++; base[i].big[0]  = 'R';
     base[i].big[1]  = 'X';
    j++; base[j].frequency = 9;
    i++; base[i].big[0]   = 'Y';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 8;
     i++; base[i].big[0]  = 'M';
     base[i].big[1]  = 'G';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'V';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'W';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'L';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'I';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'M';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'X';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 75;
    i++; base[i].big[0]  = 'F';
    base[i].big[1]  = 'D';
    j++; base[j].frequency = 60;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'T';
    j++; base[j].frequency = 54;
    i++; base[i].big[0]  = 'O';
    base[i].big[1]  = 'O';
    j++; base[j].frequency = 46;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 35;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'H';
    j++; base[j].frequency = 26;
    i++; base[i].big[0]  = 'U';
    base[i].big[1]  = 'K';
    j++; base[j].frequency = 20;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'R';
    j++; base[j].frequency = 17;
    i++; base[i].big[0]  = 'H';
    base[i].big[1]  = 'C';
    j++; base[j].frequency = 14;
    i++; base[i].big[0]  = 'Q';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 12;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'B';
    base[i].big[1]  = 'P';
    j++; base[j].frequency = 7;
    i++; base[i].big[0]  = 'P';
    base[i].big[1]  = 'V';
    j++; base[j].frequency = 6;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'S';
    j++; base[j].frequency = 5;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'N';
    j++; base[j].frequency = 4;
    i++; base[i].big[0]  = 'Z';
    base[i].big[1]  = 'Z';
    j++; base[j].frequency = 3;
    i++; base[i].big[0]  = 'M';
    base[i].big[1]  = 'J';
    j++; base[j].frequency = 2;
    i++; base[i].big[0]  = 'K';
    base[i].big[1]  = 'Q';
    j++; base[j].frequency = 1;
    i++; base[i].big[0]  = 'W';
    base[i].big[1]  = 'P';

    i=0;
    j=0;

    char **tab;
    list node = *p_l;
    int k=0;
    scytale tableau = NULL;
    int frequency=0,nbig=0;
    char big1, big2;
    double frequency_max=0,frequency2=0;
    list head_node=NULL, head_mess=NULL;
    list message=NULL;

    char* tmp=' ';
    for(i=0;i<=length(*p_l);i++){
        add_new_list(&message,&tmp,k);
        k++;
    }
    k=0;

    for(i=1;i<=length(*p_l);i++){
        for(j=1;j<=length(*p_l);j++){
            if((i*j)==length(*p_l)){
            add_new_scytale(&tableau,k,i,j);
            k++;
            }
        }
    }

    while(tableau){
        k=0;
        big1=0;
        big2=0;
        frequency=0;
        frequency2=0;
        frequency_max=0;
        nbig=0;
        node = *p_l;
        tab = (char**) malloc( tableau->tab.hauteur * sizeof(char*));

        for (i = 0 ; i < tableau->tab.hauteur ; i++)
        tab[i] =  malloc( tableau->tab.diametre * sizeof(char));

        for(j = 0 ; j < tableau->tab.diametre ; j++) {
            for (i = 0; i < tableau->tab.hauteur ; i++) {
                if(!node) tab[i][j] = ' ';
                else {
                tab[i][j] = *node->content;
                node = node->next;
                }
            }
        }

        list new_node = NULL;
        for(i = 0 ; i < tableau->tab.hauteur ; i++) {
            for (j = 0; j < tableau->tab.diametre ; j++) {
                add_new_list(&new_node,&tab[i][j],k);
                k++;
            }
        }
    head_node = new_node;
    while(new_node->next){
        if(('a'<=*new_node->next->content)&&('z'>=*new_node->next->content)&&('a'<=*new_node->content)&&('z'>=*new_node->next->content)){
            big1=*new_node->content+'A'-'a';
            big2=*new_node->next->content+'A'-'a';
            for(i=0;i<=549;i++){
              if((big1==base[i].big[0])&&(big2==base[i].big[1])) {
                  frequency = frequency+base[i].frequency;
                  nbig++;
              }
            }
        }
    new_node=new_node->next;
    }
    new_node = head_node;
    frequency2 = (double) frequency / (double) nbig;
    if(frequency2>frequency_max){
        frequency_max = frequency2;
        while(new_node){
            *message->content = *new_node->content;
            new_node=new_node->next;
            message=message->next;
        }
    }
    new_node = head_node;
    message = head_mess;
    free(tab);
    show_list(new_node);
    printf("\n\n");
    tableau = tableau->next;
    }

    printf("MESSAGE FINAL::::\n\n");

    show_list(message);



}
