#ifndef LISTE_H
#define LISTE_H

#include <stddef.h>

struct Noeud {
    int valeur;
    struct Noeud *suivant;
};

struct Liste {
    size_t taille;
    struct Noeud *premier;
};

void liste_liberer(struct Liste *l);
struct Liste *liste_creer(void);

#endif