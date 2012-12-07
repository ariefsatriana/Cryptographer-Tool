#ifndef SCYTALE_H_INCLUDED
#define SCYTALE_H_INCLUDED

typedef struct tab {
    int diametre, hauteur;
} tab;

typedef struct scytaleNode {
   tab tab;
   struct scytaleNode *next;
   struct scytaleNode *prev;
} scytaleNode;
typedef scytaleNode* scytale;

typedef struct bigramme {
    double frequency;
    char big[2];
} bigramme;

void scytale_menyu();
void scytale_cipher_menu();
void scytale_decipher_menu();
list scytale_cipher(list *p_l,int *value);
list scytale_decipher(list *p_l,int *value);
void scytale_decrypter(list *p_l);
void add_new_scytale(scytale *p_l,int position,int hauteur,int diametre);

#endif // SCYTALE_H_INCLUDED
