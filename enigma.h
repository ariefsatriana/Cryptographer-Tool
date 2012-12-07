#ifndef ENIGMA_H_INCLUDED
#define ENIGMA_H_INCLUDED

typedef struct door {
    int entry, exit;
} door;

typedef struct enigmaNode {
   door door;
   struct enigmaNode *next;
   struct enigmaNode *prev;
} enigmaNode;
typedef enigmaNode* enigma;


void menu_enigma();
void enigma_cipher_menu();
void enigma_decipher_menu();
int ascii_alphabet_enigma(char *a);
void add_new_enigma(enigma *p_l,int position);
int* convert_letter_to_number(list l);
void create_circle_enigma(enigma l);
void init_value_enigma(enigma *con,enigma *rot1,enigma *rot2,enigma *rot3,enigma *ref);
enigma init_enigma(enigma *p_l);
void enigma_cipher(list *p_l,int* key);
void enigma_decipher(list *p_l,int* key);

#endif // ENIGMA_H_INCLUDED
