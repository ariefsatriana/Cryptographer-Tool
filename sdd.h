#ifndef SDD_H_INCLUDED
#define SDD_H_INCLUDED

    typedef struct listNode {
        char* content;
        struct listNode* next;
        struct listNode* prev;
    } listNode;
    typedef listNode* list;

    /*
     * Structures de bases avec les listes chain�es
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
typedef stackNode* pile; // remplacer "char*" par le type appropri�

typedef struct fileNode
{
    int depth;
    list top;
    list queue;
} fileNode;
typedef fileNode* file; // remplacer "int*" par le type appropri�

// GESTIONNAIRE DE PILE

/**
 * Initialise une pile.
 *
 * Retourne : une valeur/structure repr�sentant une pile vide.
 */

pile initPile();

/**
 * D�termine si la pile sp�cifi�e est vide.
 *
 * Param�tre p : la pile � examiner.
 *
 * Retourne : 1 si p est vide et 0 sinon.
 */

int estVideP(pile p);

/**
 * Empile la valeur sp�cifi�e au sommet de la pile sp�cifi�e.
 *
 * Param�tre p : pointeur vers la pile � manipuler.
 * Param�tre v : valeur � empiler sur p.
 *
 * Retourne : -1 si un param�tre est incorrect, 1 sinon.
 */

int empiler(pile* p,char* v);

/**
 * D�pile la valeur au sommet de la pile sp�cifi�e et la range � l'adresse
 * sp�cifi�e.
 *
 * Param�tre p : pointeur vers la pile � manipuler.
 * Param�tre v : pointeur vers l'entier o� stocker le sommet de p.
 *
 * Retourne : -1 si un param�tre est incorrect, 0 si la pile �tait vide
 * avant l'op�ration et 1 sinon.
 */

int depiler(pile* p, char* v);

/**
 * Range � l'adresse sp�cifi�e la valeur au sommet de la pile sp�cifi�e. La
 * pile n'est pas modifi�e.
 *
 * Param�tre p : la pile � examiner.
 * Param�tre v : pointeur vers l'entier o� stocker le sommet de p.
 *
 * Retourne : -1 si un param�tre est incorrect, 0 si la pile est vide
 * et 1 sinon.
 */

int sommet(pile p, char* v);


// GESTIONNAIRE DE FILE

/**
 * Initialise une file
 *
 * Retourne : une valeur/structure repr�sentant une file vide.
 */
file initFile();

/**
 * D�termine la taille de la file sp�cifi�e.
 *
 * Param�tre f : la file � examiner.
 *
 * Retourne : la taille de f.
 */
int taille(file f);

/**
 * D�termine si la file sp�cifi�e est vide.
 *
 * Param�tre f : la file � examiner.
 *
 * Retourne : 1 si f est vide et 0 sinon.
 */
int estVideF(file f);

/**
 * Ajoute la valeur sp�cifi�e � la fin de la file sp�cifi�e.
 *
 * Param�tre f : pointeur vers la file � manipuler.
 * Param�tre v : valeur � ajouter � f.
 *
 * Retourne : -1 si un param�tre est incorrect, 1 sinon.
 */

int enfiler(file* f, char* v);

/**
 * Retire la valeur de d�but de la file sp�cifi�e et la range � l'adresse
 * sp�cifi�e.
 *
 * Param�tre f : pointeur vers la file � manipuler.
 * Param�tre v : pointeur vers l'entier o� stocker le d�but de f.
 *
 * Retourne : -1 si un param�tre est incorrect, 0 si la file �tait vide
 * avant l'op�ration et 1 sinon.
 */
int defiler(file* f, char* v);

/**
 * Range � l'adresse sp�cifi�e la valeur de d�but de la file sp�cifi�e. La file
 * n'est pas modifi�e.
 *
 * Param�tre f : la file � examiner.
 * Param�tre v : pointeur vers l'entier o� stocker le d�but de f.
 *
 * Retourne : -1 si un param�tre est incorrect, 0 si la file est vide
 * et 1 sinon.
 */
int debut(file f, char* v);

/**
 * Range � l'adresse sp�cifi�e la valeur de fin de file sp�cifi�e. La file
 * n'est pas modifi�e.
 *
 * Param�tre f : la file � examiner.
 * Param�tre v : pointeur vers l'entier o� stocker la fin de f.
 *
 * Retourne : -1 si un param�tre est incorrect, 0 si la file est vide
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
