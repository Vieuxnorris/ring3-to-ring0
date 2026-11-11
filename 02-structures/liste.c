#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

int liste_echec_malloc = 0;

void liste_liberer(struct Liste *l, size_t *nb_free) {
    if (l != NULL) {
        struct Noeud *p = l->premier;
        while(p != NULL) {
            struct Noeud *tmp = p;
            p = p->suivant;
            free(tmp);
            if (nb_free != NULL) {
                *nb_free += 1;
            }
        }
        free(l);
        if (nb_free != NULL) {
            *nb_free += 1;
        }
    }
}

struct Liste *liste_creer(void) {
    struct Liste *l = NULL;
    if (liste_echec_malloc == 0) {
        l = malloc(sizeof(struct Liste));
    }
    if (l == NULL) {
        return NULL;
    }

    l->taille = 0;
    l->premier = NULL;
    return l;
}

// RETOUR : adresse du nouveau noeud, ou NULL si le malloc echoue
// LISTE VIDE : apres l'ajout, premier = n , taille = 1 , n->suivant = NULL
// ECHEC MALLOC : la liste reste la même (premier et taille inchangés, aucun noeud libere)
struct Noeud *liste_ajouter_fin(struct Liste *l, int valeur) {
    struct Noeud *n = NULL;
    if (liste_echec_malloc == 0) {
        n = malloc(sizeof(struct Noeud));
    }
    if (n == NULL) {
        return NULL;
    }
    
    n->valeur = valeur;
    n->suivant = NULL;
    if (l->premier == NULL) {
        l->premier = n;
    } else {
        struct Noeud *p = l->premier;
        while (p->suivant != NULL) {
            p = p->suivant;
        }
        p->suivant = n;
    }
    l->taille++;
    return n;
}

struct Noeud *liste_ajouter_tete(struct Liste *l, int valeur) {
    struct Noeud *n = NULL;
    if (liste_echec_malloc == 0) {
        n = malloc(sizeof(struct Noeud));
    }
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