#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdd.h"
#include "cesar.h"
#include "scytale.h"
#include "vigenere.h"
#include "usefull.h"
#include "enigma.h"

#define CONTENT *node->content
#define P_CONTENT *(*p_l)->content
#define SAISIE(x) fflush(stdin); scanf("%d",&x);
#define S_GETS(x) fflush(stdin); gets(x);
#define DC(a,b) (a - b)
#define CC(a,b,c) (a+b-c) % 26 + c
#define CD(a,b,c) ((a-b-c) + 26) % 26 + c
#define RAND() rand() % 26


void enigma_menu() {
    int choice;

    // Présentation

    printf("Enigma \n\n");
    printf("Menu\n\n");
    printf("1 - Chiffrage \n");
    printf("2 - Dechiffrage \n\n");
    s_scanf(&choice,1,2);

    if(choice == 1) enigma_cipher_menu();
    else if (choice == 2) enigma_decipher_menu();
}

void enigma_cipher_menu() {

    // initialisation des variables

    char str[400]; // la phrase à crypter
    list node = NULL; // la liste chainée
    int i, key[3]; // le compteur, le choix, la clé

    //  Présentation

    printf("Cryptage - Enigma : \n\n");
    printf("Veuillez saisir votre phrase a crypter : ");
    S_GETS(str);

    // Mise en place de la liste chainée

    for(i=0; i<strlen(str); i++) add_new_list(&node,&str[i],i);

    // Menu du choix de la clé

    enigma_cipher(&node,key);

    // On met la liste dans une chaine de caractère

    printf("Phrase cryptee : ");
    show_list(node);

    // La petite phrase d'avertissement

    printf("\n\nVeuillez notez votre phrase... \n");
    printf("\n");

    // Vidage de la mémoire
    free_list(&node);
}

void enigma_decipher_menu() {

    // initialisation des variables

    char str[400]; // la phrase à crypter
    list node = NULL; // la liste chainée
    int i,key[3]; // le compteur, le choix, la clé

    //  Présentation

    printf("dechiffrage - Enigma : \n\n");
    printf("Veuillez saisir votre phrase a dechiffrer : ");
    S_GETS(str);

    // Mise en place de la liste chainée

    for(i=0; i<strlen(str); i++) add_new_list(&node,&str[i],i);

    // Menu du choix de la clé
    enigma_decipher(&node,key); // Algo de chiffrage

    // On met la liste dans une chaine de caractère

    printf("Phrase decryptee : ");
    show_list(node);

    // La petite phrase d'avertissement

    printf("\n\nVeuillez notez votre phrase... \n");
    printf("\n");

    // Vidage de la mémoire
    free_list(&node);
}

int ascii_alphabet_enigma(char *a) {
     if(*a >= 'A' && *a <= 'Z') return *a - 'A';
     else if(*a >= 'a' && *a <= 'z') return *a -'a';
     return *a - 'a';
}

int* convert_letter_to_number(list l) {
    int i = 0;
    int taille = length(l);
    int *tab = (int*) malloc( taille * sizeof(int));

    while(l) {
        tab[i] = ascii_alphabet_enigma(l->content);
        i++;
        l = l->next;
    }
    return tab;
}

enigma init_enigma(enigma *p_l) {
    int i; for (i = 0; i < 26 ; i++) add_new_enigma(p_l,i);
    create_circle_enigma(*p_l);
    return *p_l;
}

void init_value_enigma(enigma *con,enigma *rot1,enigma *rot2,enigma *rot3,enigma *ref) {

    int i;

    int tab_con[26] = {
        2, 1, 0,
        5, 4, 3,
        8, 7, 6,
        11, 10, 9,
        14, 13, 12,
        17, 16, 15,
        20, 19, 18,
        23, 22, 21,
        25, 24
    };
    int tab_rot1[26] = {
        4, 0, 5,
        1, 3, 2,
        10, 6, 11,
        7, 9, 8,
        16, 12, 17,
        13, 15, 14,
        22, 18, 24,
        19, 21, 20,
        23, 25,
    };
    int tab_rot2[26] = {
        5, 3, 0,
        2, 1, 4,
        11, 9, 6,
        8, 7, 10,
        17, 15, 12,
        14, 13, 16,
        23, 21, 18,
        20, 19, 22,
        25, 24
    };
    int tab_rot3[26] = {
        0, 19, 20,
        1, 18, 21,
        2, 17, 22,
        3, 16, 23,
        4, 15, 24,
        5, 14, 25,
        6, 13,
        7, 12,
        8, 11,
        9, 10
    };
    int tab_ref[26] = {
        3, 2, 1,
        0, 5, 4,
        9, 8, 7,
        6, 11, 10,
        15, 14, 13,
        12, 17, 16,
        21, 20, 19,
        18, 23, 22,
        24, 25
    };

    enigma head_con = *con;
    enigma head_rot1 = *rot1;
    enigma head_rot2 = *rot2;
    enigma head_rot3 = *rot3;
    enigma head_ref = *ref;

    for (i = 0 ; i < 26 ; i++) {
        head_con->door.entry = head_rot1->door.entry =
        head_rot2->door.entry = head_rot3->door.entry = head_ref->door.entry = i;

        head_con->door.exit = tab_con[i];

        head_rot1->door.exit = tab_rot1[i];
        head_rot2->door.exit = tab_rot2[i];
        head_rot3->door.exit = tab_rot3[i];

        head_ref->door.exit = tab_ref[i];

        head_con = head_con->next;

        head_rot1 = head_rot1->next;
        head_rot2 = head_rot2->next;
        head_rot3 = head_rot3->next;

        head_ref = head_ref->next;
    }

}

void add_new_enigma(enigma *p_l,int position) {
    enigma node = (enigma) malloc(sizeof(enigmaNode));
    node->door.entry = node->door.exit = 0;

    if (!*p_l || !position) {
        *p_l = node;
        node->next = NULL;
        node->prev = NULL;
        return;
    }
    enigma oldList = *p_l;

    while (oldList->next) oldList = oldList->next;

    node->next = oldList->next;
    node->prev = oldList;
    oldList->next = node;
}


void create_circle_enigma(enigma l) {
    enigma node = l;
    while (l->next) l = l->next;
    if (l->prev) node->prev = l;
    l->next = node;
}

void rotate(enigma *p_l) {
    if(!p_l) return;
    enigma node = *p_l;
    if(!node) return;
    node = node->next;
    *p_l = node;
    int cpt = -1;
    do {
        cpt++;
        node->door.entry = cpt;
        node->door.exit = node->door.exit--;
        if(node->door.exit < 0) node->door.exit = 25;
        node = node->next;
    } while(node != *p_l);
}

void enigma_cipher(list *p_l,int* key) {

    int i;
    list node = *p_l;
    char str[3];

    // mise en place du connecteur
    enigma connector = init_enigma(&connector);

    // mise en place des rotors
    enigma rotor1 = init_enigma(&rotor1);
    enigma rotor2 = init_enigma(&rotor2);
    enigma rotor3 = init_enigma(&rotor3);

    // mise en place du réflecteur
    enigma reflector = init_enigma(&reflector);

    // mise en place de la phrase à chiffrer
    int *tab = convert_letter_to_number(*p_l);

    // initialisation
    init_value_enigma(&connector,&rotor1,&rotor2,&rotor3,&reflector);

    printf("Veuillez saisir votre cle (composee de 3 lettres de l'alphabet) : ");
    S_GETS(str);
    key[0] = str[0]-'a';
    key[1] = str[1]-'a';
    key[2] = str[2]-'a';
    while(rotor1->door.entry!=key[0]) rotor1 = rotor1->next;
    while(rotor2->door.entry!=key[1]) rotor2 = rotor2->next;
    while(rotor3->door.entry!=key[2]) rotor3 = rotor3->next;

    enigma head_con = connector;
    enigma head_rot1 = rotor1;
    enigma head_rot2 = rotor2;
    enigma head_rot3 = rotor3;
    enigma head_ref = reflector;

    int cpt_rotor2 = 0;

    // algo
    for(i = 0 ; i < length(*p_l) ; i++) {

        if(!(tab[i] < 0 || tab[i] > 25)) {

        head_con = connector;
        head_rot1 = rotor1;
        head_rot2 = rotor2;
        head_rot3 = rotor3;
        head_ref = reflector;

        // Chemin aller
        while(head_con->door.entry != tab[i]) head_con = head_con->next;
        while(head_rot1->door.entry != head_con->door.exit) head_rot1 = head_rot1->next;
        while(head_rot2->door.entry != head_rot1->door.exit) head_rot2 = head_rot2->next;
        while(head_rot3->door.entry != head_rot2->door.exit) head_rot3 = head_rot3->next;
        while(head_ref->door.entry != head_rot3->door.exit) head_ref = head_ref->next;

        head_con = connector;
        head_rot1 = rotor1;
        head_rot2 = rotor2;
        head_rot3 = rotor3;

        // Chemin retour
        while(head_rot3->door.exit != head_ref->door.exit) head_rot3 = head_rot3->next;
        while(head_rot2->door.exit != head_rot3->door.entry) head_rot2 = head_rot2->next;
        while(head_rot1->door.exit != head_rot2->door.entry) head_rot1 = head_rot1->next;
        while(head_con->door.exit != head_rot1->door.entry) head_con = head_con->next;
        tab[i] = head_con->door.entry;

        // Rotation
        rotate(&rotor1);
        cpt_rotor2++;
        if(!(cpt_rotor2 % 26)) rotate(&rotor2);
        if(!(cpt_rotor2 % (676))) rotate(&rotor3);
        }

    }

    for(i = 0; i < length(*p_l) ; i++) {
        *node->content = tab[i] + 'a';
        node = node->next;
    }
}

void enigma_decipher(list *p_l,int* key) {

    int i;
    list node = *p_l;
    char str[3];

    // mise en place du connecteur
    enigma connector = init_enigma(&connector);

    // mise en place des rotors
    enigma rotor1 = init_enigma(&rotor1);
    enigma rotor2 = init_enigma(&rotor2);
    enigma rotor3 = init_enigma(&rotor3);

    // mise en place du réflecteur
    enigma reflector = init_enigma(&reflector);

    // mise en place de la phrase à déchiffrer
    int *tab = convert_letter_to_number(*p_l);

    // initialisation
    init_value_enigma(&connector,&rotor1,&rotor2,&rotor3,&reflector);

    printf("Veuillez saisir votre cle (composee de 3 lettres de l'alphabet) : ");
    S_GETS(str);
    key[0] = str[0]-'a';
    key[1] = str[1]-'a';
    key[2] = str[2]-'a';
    while(rotor1->door.entry!=key[0]) rotor1 = rotor1->next;
    while(rotor2->door.entry!=key[1]) rotor2 = rotor2->next;
    while(rotor3->door.entry!=key[2]) rotor3 = rotor3->next;

    enigma head_con = connector;
    enigma head_rot1 = rotor1;
    enigma head_rot2 = rotor2;
    enigma head_rot3 = rotor3;
    enigma head_ref = reflector;

    int cpt_rotor2 = 0;

    // algo
    for(i = 0 ; i < length(*p_l) ; i++) {

        if(!(tab[i] < 0 || tab[i] > 25)) {

        head_con = connector;
        head_rot1 = rotor1;
        head_rot2 = rotor2;
        head_rot3 = rotor3;
        head_ref = reflector;

        // Chemin aller
        while(head_con->door.entry != tab[i]) head_con = head_con->next;
        while(head_rot1->door.entry != head_con->door.exit) head_rot1 = head_rot1->next;
        while(head_rot2->door.entry != head_rot1->door.exit) head_rot2 = head_rot2->next;
        while(head_rot3->door.entry != head_rot2->door.exit) head_rot3 = head_rot3->next;
        while(head_ref->door.entry != head_rot3->door.exit) head_ref = head_ref->next;

        head_con = connector;
        head_rot1 = rotor1;
        head_rot2 = rotor2;
        head_rot3 = rotor3;

        // Chemin retour
        while(head_rot3->door.exit != head_ref->door.exit) head_rot3 = head_rot3->next;
        while(head_rot2->door.exit != head_rot3->door.entry) head_rot2 = head_rot2->next;
        while(head_rot1->door.exit != head_rot2->door.entry) head_rot1 = head_rot1->next;
        while(head_con->door.exit != head_rot1->door.entry) head_con = head_con->next;
        tab[i] = head_con->door.entry;

        // Rotation
        rotate(&rotor1);
        cpt_rotor2++;
        if(!(cpt_rotor2 % 26)) rotate(&rotor2);
        if(!(cpt_rotor2 % (676))) rotate(&rotor3);
        }

    }

    for(i = 0; i < length(*p_l) ; i++) {
        *node->content = tab[i] + 'a';
        node = node->next;
    }
    printf("\n");

}
