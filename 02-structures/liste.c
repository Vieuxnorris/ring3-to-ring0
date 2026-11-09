#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

void liste_liberer(struct Liste *l) {
    if (l != NULL) {
        free(l);
    } else {
        printf("Liste NULL no free memory needed\n");
    }
}

struct Liste *liste_creer(void) {
    struct Liste *l = malloc(sizeof(struct Liste));
    if (l == NULL) {
        return NULL;
    }

    l->taille = 0;
    l->premier = NULL;
    return l;
}

struct Noeud *liste_ajouter_tete(struct Liste *l, int valeur) {
    struct Noeud *n = malloc(sizeof(struct Noeud));
    if (n == NULL) {
        return NULL;
    }

    n->valeur = valeur;
    n->suivant = l->premier;
    l->premier = n;

    l->taille++;

    return n;
}

void afficher_valeur(struct Liste *l) {
    struct Noeud *p = l->premier;
    while(p != NULL) {
        printf("valeur:%d ", p->valeur);
        p = p->suivant;
    }
    printf("\n");
}

int liste_lire(struct Liste *l, size_t indice, int *buffer) {
    if (l != NULL && indice < l->taille) {
        struct Noeud *p = l->premier;
        for(size_t i=0; i < indice; i++) {
            p = p->suivant;
        }
        *buffer = p->valeur;
        return 0;
    }
    return 1;
}