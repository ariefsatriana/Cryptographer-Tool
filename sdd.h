#ifndef SDD_H_INCLUDED
#define SDD_H_INCLUDED

    typedef struct listNode {
        char* content;
        struct listNode* next;
        struct listNode* prev;
    } listNode;
    typedef listNode* list;

    /*
     * Structures de bases avec les listes chainées
     * -> Ajout
     * -> Affichage
     */

    void add_new_list(list *p_l,char *value,unsigned position);
    void show_list(list l);
    void create_circle_list(list l);

typedef struct stackNode
{
    int depth;
    list top;
} stackNode;
typedef stackNode* pile; // remplacer "char*" par le type approprié

typedef struct fileNode
{
    int depth;
    list top;
    list queue;
} fileNode;
typedef fileNode* file; // remplacer "int*" par le type approprié

// GESTIONNAIRE DE PILE

/**
 * Initialise une pile.
 *
 * Retourne : une valeur/structure représentant une pile vide.
 */

pile initPile();

/**
 * Détermine si la pile spécifiée est vide.
 *
 * Paramètre p : la pile à examiner.
 *
 * Retourne : 1 si p est vide et 0 sinon.
 */

int estVideP(pile p);

/**
 * Empile la valeur spécifiée au sommet de la pile spécifiée.
 *
 * Paramètre p : pointeur vers la pile à manipuler.
 * Paramètre v : valeur à empiler sur p.
 *
 * Retourne : -1 si un paramètre est incorrect, 1 sinon.
 */

int empiler(pile* p,char* v);

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

int depiler(pile* p, char* v);

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

int sommet(pile p, char* v);


// GESTIONNAIRE DE FILE

/**
 * Initialise une file
 *
 * Retourne : une valeur/structure représentant une file vide.
 */
file initFile();

/**
 * Détermine la taille de la file spécifiée.
 *
 * Paramètre f : la file à examiner.
 *
 * Retourne : la taille de f.
 */
int taille(file f);

/**
 * Détermine si la file spécifiée est vide.
 *
 * Paramètre f : la file à examiner.
 *
 * Retourne : 1 si f est vide et 0 sinon.
 */
int estVideF(file f);

/**
 * Ajoute la valeur spécifiée à la fin de la file spécifiée.
 *
 * Paramètre f : pointeur vers la file à manipuler.
 * Paramètre v : valeur à ajouter à f.
 *
 * Retourne : -1 si un paramètre est incorrect, 1 sinon.
 */

int enfiler(file* f, char* v);

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
int defiler(file* f, char* v);

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
int debut(file f, char* v);

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

int fin(file f, char* v);

/*
 * Taille de la liste
 */

int length(list l);
int length2(list l);

void convert_list_to_string(list *node,char **str);

void free_list(list *p_l);

#endif // SDD_H_INCLUDED
