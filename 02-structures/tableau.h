#ifndef TABLEAU_H
#define TABLEAU_H

#include <stddef.h>

struct Tableau {
    int *donnees;
    size_t taille;
    size_t capacite;
};

void tableau_liberer(struct Tableau *t);
int tableau_lire(struct Tableau *t, size_t indice, int *buffer);
int tableau_ajouter(struct Tableau *t, int valeur);
void afficher_valeur(struct Tableau *t);
struct Tableau *tableau_creer(size_t capacite);

#endif