#ifndef CESAR_H_INCLUDED
#define CESAR_H_INCLUDED

#include "sdd.h"

void cesar();
void cesar_cipher_menu();
void cesar_cipher(list *p_l,int *key);
void cesar_cipher2(list *p_l,int *key,int *pos);
void cesar_decipher_menu();
void cesar_decipher(list *p_l,int *key);
void cesar_decipher2(list *p_l,int *key,int *pos);
void cesar_decrypter(list *p_l);

#endif // CESAR_H_INCLUDED
