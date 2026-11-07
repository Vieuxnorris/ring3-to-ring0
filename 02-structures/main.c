#include "tableau.h"
#include <stdio.h>

int main() {
    const size_t nb_ajouts = 1000;
    struct Tableau *t = tableau_creer(0);
    if (t == NULL) {
        return 1;
    }

    int valid;
    for(size_t i=0; i<nb_ajouts; i++) {
        valid = tableau_ajouter(t, (int)i-500);
        if (valid != 0) {
            printf("ERROR ajout sur l'indice: %zu\n", i);
            tableau_liberer(t);
            return 1;
        }
    }

    if(t->taille != nb_ajouts) {
        printf("ERROR taille:%zu == attendu:%zu\n", t->taille, nb_ajouts);
        tableau_liberer(t);
        return 1;
    }
    printf("taille=%zu - capacite=%zu\n", t->taille, t->capacite);
    
    int v;
    for(size_t i=0; i<nb_ajouts;i++) {
        if(tableau_lire(t, i, &v) == 0) {
            if (v != (int)i-500) {
                printf("indice: %zu attendu: %d, lu: %d\n", i, (int)i-500, v);
                tableau_liberer(t);
                return 1;
            }
        } else {
            printf("ERROR\n");
            tableau_liberer(t);
            return 1;
        }
    }

    printf("OK : 1000 valeurs verifiees.\n");
    tableau_liberer(t);
    return 0;
}