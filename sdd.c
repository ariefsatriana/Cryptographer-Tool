#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdd.h"
#include "cesar.h"

/*
 * Fonction de création de liste chainée :
 * Pour ce projet :
 * -> Ajouter dans chaque maillon, un caractère de la phrase
 */

void convert_list_to_string(list *node,char **str) {
    int i = 0;
    int taille = length(*node);
    *str = malloc(taille * sizeof(char*));

    list l = *node;
    while(l) {
        (*str)[i] = *l->content; i++;
        l = l->next;
    }
}

void add_new_list(list *p_l,char *value,unsigned position) {
    list node = (list) malloc(sizeof(listNode));
    node->content = value;

    if (!position) {
        node->next = *p_l;
        node->prev = NULL;
        *p_l = node;
        return;
    }
    list oldList = *p_l;

    while (oldList->next && position > 1) oldList = oldList->next;
    node->next = oldList->next;
    node->prev = NULL;

    if (oldList->next) node->prev->next = NULL;
    oldList->next = node;
}

/*
 * Fonction d'affichage de contenu de liste
 * -> On défile la liste et à chaque fois on affiche le contenu de chaque
 *    maillon.
 */

void show_list(list l)
{
    if (!l) return;
    list node = l;
    if (l->next == l)
    {
        printf("%c ...",*l->content);
        return;
    }
    list top = l;

    do
    {
        if (!l->next) (l->prev) ? printf("%c",*l->content) : printf("%c",*l->content);
        else if ( !l->prev ) printf("%c",*l->content);
        else if ( l == node && l->prev ) printf("%c",*l->content);
        else if ( l->prev ) printf("%c",*l->content);

        l = l->next;
        if (!l) return;
    }
    while (l != top);
    if (l == top) printf(" ...");
}

void create_circle_list(list l) {
    list node = l;
    while (l->next) l = l->next;
    if (l->prev) node->prev = l;
    l->next = node;
}



pile initPile() {
    pile s = NULL;
    s = malloc(sizeof(stackNode));
    s->top = NULL;
    s->depth = 0;
    return s;
}

/**
 * Détermine si la pile spécifiée est vide.
 *
 * Paramètre p : la pile à examiner.
 *
 * Retourne : 1 si p est vide et 0 sinon.
 */
int estVideP(pile p) {
    if (!p->depth) return 1;
    else return 0;
}

/**
 * Empile la valeur spécifiée au sommet de la pile spécifiée.
 *
 * Paramètre p : pointeur vers la pile à manipuler.
 * Paramètre v : valeur à empiler sur  p.
 *
 * Retourne : -1 si un paramètre est incorrect, 1 sinon.
 */

int empiler(pile* p, char* v) {
    if (!p) return -1;
    list node = NULL;
    node = malloc(sizeof(listNode));
    node->content = v;
    node->next = (*p)->top;
    (*p)->top = node;
    (*p)->depth++;
    return 1;
}

/**
 * Dépile la valeur au sommet de la pile spécifiée et la range à l'adresse
 * spécifiée.
 *
 * Paramètre p : pointeur vers la pile à manipuler.
 * Paramètre v : pointeur vers l'entier où stocker le sommet de p.
 *
 * Retourne : -1 si un paramètre est incorrect, 0 si la pile était vide
 * avant l'opération et 1 sinon.
 */

int depiler(pile* p, char* v) {
    list node = NULL;
    if (!*p || !*v || ( !*p && !*v )) return -1;
    if (!estVideP(*p)) {
        v = (*p)->top->content;
        (*p)->depth--;
        node = (*p)->top;
        (*p)->top = (*p)->top->next;
        free(node);
        return 1;
    } else return 0;
}

/**
 * Range à l'adresse spécifiée la valeur au sommet de la pile spécifiée. La
 * pile n'est pas modifiée.
 *
 * Paramètre p : la pile à examiner.
 * Paramètre v : pointeur vers l'entier où stocker le sommet de p.
 *
 * Retourne : -1 si un paramètre est incorrect, 0 si la pile est vide
 * et 1 sinon.
 */
int sommet(pile p, char* v) {
    if ( !p || !*v || (!p && !*v)) return -1;
    if (!estVideP(p)) {
        v = p->top->content;
        return 1;
    } else return 0;
}


// GESTIONNAIRE DE FILE

/**
 * Initialise une file
 *
 * Retourne : une valeur/structure représentant une file vide.
 */
file initFile() {
    file f;
    f = malloc(sizeof(fileNode));
    f->top = NULL;
    f->queue = NULL;
    f->depth = 0;
    return f;
}

/**
 * Détermine la taille de la file spécifiée.
 *
 * Paramètre f : la file à examiner.
 *
 * Retourne : la taille de f.
 */
int taille(file f) {
    return f->depth;
}

/**
 * Détermine si la file spécifiée est vide.
 *
 * Paramètre f : la file à examiner.
 *
 * Retourne : 1 si f est vide et 0 sinon.
 */
int estVideF(file f) {
    if (!f->depth) return 1;
    else return 0;
}

/**
 * Ajoute la valeur spécifiée à la fin de la file spécifiée.
 *
 * Paramètre f : pointeur vers la file à manipuler.
 * Paramètre v : valeur à ajouter à f.
 *
 * Retourne : -1 si un paramètre est incorrect, 1 sinon.
 */
int enfiler(file* f, char* v) {
    if (!f) return -1;
    list node = malloc(sizeof(listNode));
    node->content = v;
    node->next = NULL;

    if (!(*f)->top) {
        (*f)->top = node;
        (*f)->queue = node;
    } else {
        (*f)->queue->next = node;
        (*f)->queue = node;
    }
    (*f)->depth++;
    return 1;
}

/**
 * Retire la valeur de début de la file spécifiée et la range à l'adresse
 * spécifiée.
 *
 * Paramètre f : pointeur vers la file à manipuler.
 * Paramètre v : pointeur vers l'entier où stocker le début de f.
 *
 * Retourne : -1 si un paramètre est incorrect, 0 si la file était vide
 * avant l'opération et 1 sinon.
 */

int defiler(file* f, char* v) {
    if ( !f || !v || (!f && !v)) return -1;
    if (!estVideF(*f)) {
        v = (*f)->top->content;
        (*f)->depth--;
        list node = (*f)->top;
        (*f)->top = (*f)->top->next;
        free(node);
        if (!(*f)->depth) (*f)->queue = NULL;
        return 1;
    } else return 0;
}

/**
 * Range à l'adresse spécifiée la valeur de début de la file spécifiée. La file
 * n'est pas modifiée.
 *
 * Paramètre f : la file à examiner.
 * Paramètre v : pointeur vers l'entier où stocker le début de f.
 *
 * Retourne : -1 si un paramètre est incorrect, 0 si la file est vide
 * et 1 sinon.
 */

int debut(file f, char* v) {
    if (!v) return -1;
    if (estVideF(f)) return 0;
    v = f->top->content;
    printf("\nVALEUR : %d\n",*v);
    return 1;
}
/**
 * Range à l'adresse spécifiée la valeur de fin de file spécifiée. La file
 * n'est pas modifiée.
 *
 * Paramètre f : la file à examiner.
 * Paramètre v : pointeur vers l'entier où stocker la fin de f.
 *
 * Retourne : -1 si un paramètre est incorrect, 0 si la file est vide
 * et 1 sinon.
 */

int fin(file f, char* v) {
    if (!v) return -1;
    if (estVideF(f)) return 0;
    else {
        v = f->queue->content;
        return 1;
    }
}

/*
 * Taille de la liste
 */

int length(list l)
{
    int i = 0;
    while(l) {
        i++;
        l = l->next;
    }
    return i;
}

int length2(list l)
{
    int i = 0;
    while(l) {
            if( (*l->content >= 'A' && *l->content <= 'Z') ||
                    (*l->content >= 'a' && *l->content <= 'z') )
                i++;
        l = l->next;
    }
    return i;
}


void free_list(list *p_l) {
    list node = *p_l;
    while((*p_l)->next) {
        node = *p_l;
        *p_l = (*p_l)->next;
        free(node);
    }
    free(*p_l);
}
