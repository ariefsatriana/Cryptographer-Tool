#ifndef VIGENERE_H_INCLUDED
#define VIGENERE_H_INCLUDED

#include "sdd.h"

void vigenere();
void vigenere_cipher_menu();
void vigenere_decipher_menu();
void vigenere_cipher(list* p_l,char* key);
void vigenere_decipher(list* p_l,char* key);
void vigenere_decrypter(list* p_l,char *str);

double indice(double l,double n);

#endif // VIGENERE_H_INCLUDED
