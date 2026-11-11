#ifndef LISTE_H
#define LISTE_H

#include <stddef.h>

extern int liste_echec_malloc;

struct Noeud {
    int valeur;
    struct Noeud *suivant;
};

struct Liste {
    size_t taille;
    struct Noeud *premier;
};

void liste_liberer(struct Liste *l, size_t *nb_free);
struct Liste *liste_creer(void);
int liste_lire(struct Liste *l, size_t indice, int *buffer);
struct Noeud *liste_ajouter_tete(struct Liste *l, int valeur);
struct Noeud *liste_ajouter_fin(struct Liste *l, int valeur);
void afficher_valeur(struct Liste *l);

#endif