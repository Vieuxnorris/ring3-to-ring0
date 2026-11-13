#include "liste.h"
#include <stdio.h>

enum {
    MAX_INDEX=3
};

const int ajouts_invers[] = {30,20,10};
const int ajouts_order[] = {10,20,30};
const int test_delete[] = {10,30};
const int test_delete_m[] = {20,30};
const int test_delete_l[] = {20};

// return 1 : si la valeur de p n'est pas conforme a attendu[index]
// return 1 : si P a un index en trop
// return 1 : index n'est pas égal a nb_attendu
// retunr 1 : si la taille de la liste n'est pas conforme
// return 0 : if tout les test sont bon
int verifier_liste(struct Liste *l, const int *attendu, size_t nb_attendu) {
    struct Noeud *p = l->premier;
    size_t index = 0;
    while (p != NULL && index != nb_attendu) {
        if (attendu[index] != p->valeur) { 
            printf("ERROR p->valeur non conforme index:%zu index_value:%d valeur_p:%d\n", index, attendu[index],p->valeur);
            return 1;
        }
        index++;
        p = p->suivant;
    }

    if (p != NULL) {
        printf("ERREUR noeud de trop apres index %zu\n", index);
        return 1;
    }
    if (index != nb_attendu) {
        printf("ERROR INDEX MAX - index_valeur:%zu max_index:%zu\n", index, nb_attendu);
        return 1;
    }
    if (l->taille != nb_attendu) {
        printf("ERREUR taille: %zu attendu %zu\n", l->taille, nb_attendu);
        return 1;
    }

    return 0;
}

int main(void) {
    size_t nb_free = 0;
    size_t nb_free_compare = 0;

    liste_liberer(NULL, NULL);
    struct Liste *l = liste_creer();
    nb_free_compare++;
    struct Noeud *n;
    if (l == NULL) {
        printf("ERROR ALLOC List\n");
        liste_liberer(l, NULL);
        return 1;
    }
    printf("taille:%zu - adresse:0x%p\n", l->taille, l->premier);

    // Check ajout + taille
    for (size_t i=0; i<MAX_INDEX;i++) {
        n = liste_ajouter_tete(l,ajouts_invers[i]);
        if (n == NULL) {
            printf("ERROR ALLOC Noeud 1\n");
            liste_liberer(l, &nb_free);
            return 1;
        }
        printf("taille:%zu - adresse:0x%p\n", l->taille, l->premier);
        nb_free_compare++;
    }
    if (verifier_liste(l, ajouts_order, MAX_INDEX) != 0) {
        liste_liberer(l, &nb_free);
        return 1;
    }

    afficher_valeur(l);

    for (size_t i=0; i<3;i++) {
        int buffer = 777;
        if(liste_lire(l, i, &buffer) == 0) {
            if(buffer == ajouts_order[i]) {
                printf("test 1 -- buffer:%d - valeur_ajouts:%d\n", buffer, ajouts_order[i]);
            } else {
                printf("ERROR test 1 -- buffer:%d - valeur_ajouts:%d\n", buffer, ajouts_order[i]);
                liste_liberer(l, &nb_free);
                return 1;
            }
        }
        else {
            printf("ERROR test 1 : indice %zu refuse\n", i);
            liste_liberer(l, &nb_free);
            return 1;
        }
    }
    int buffer = 777;
    if (liste_lire(l, 3, &buffer) == 0) {
        printf("ERROR test 2 -- indice 3 accepte\n");
        liste_liberer(l, &nb_free);
        return 1;
    } else {
        if (buffer != 777) {
            printf("ERROR test 2 -- buffer:%d\n", buffer);
            liste_liberer(l, &nb_free);
            return 1;
        }
        printf("test 2 -- buffer:%d\n", buffer);
    }
    if (liste_delete(l, 20, &nb_free) != 0) {
        printf("ERROR - FAIL DELETE RECORD\n");   
        liste_liberer(l, &nb_free);
        return 1;
    }
    if (verifier_liste(l, test_delete, 2) != 0) {
        liste_liberer(l, &nb_free);
        return 1;
    }
    afficher_valeur(l);

    struct Liste *m = liste_creer();
    nb_free_compare++;
    if (m == NULL) {
        printf("ERROR ALLOC List\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, NULL);
        return 1;
    }
    if (liste_lire(m, 0, &buffer) == 0) {
        printf("ERROR test 3 : liste vide acceptee\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    } else {
        if (buffer != 777) {
            printf("ERROR test 3 -- buffer:%d\n", buffer);
            liste_liberer(l, &nb_free);
            liste_liberer(m, &nb_free);
            return 1;
        }
        printf("test 3 -- buffer:%d\n", buffer);
    }

    for(size_t i=0; i<MAX_INDEX;i++) {
        n = liste_ajouter_fin(m, ajouts_invers[i]);
        if (n == NULL) {
            printf("ERREUR malloc\n");
            liste_liberer(l, &nb_free);
            liste_liberer(m, &nb_free);
            return 1;
        }
        printf("valeur n:%d ", n->valeur);
        nb_free_compare++;
    }
    printf("\n");

    struct Noeud *tmp = m->premier;
    liste_echec_malloc = 1;
    n = liste_ajouter_fin(m, 50);
    liste_echec_malloc = 0;
    if (n != NULL) {
        printf("n n'est pas NULL\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    if (m->premier != tmp) {
        printf("ERROR liste différent de la save temporaire (address)\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    if (verifier_liste(m, ajouts_invers, MAX_INDEX) != 0) {
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }

    printf("INIT TEST\n");
    afficher_valeur(l);
    afficher_valeur(m);
    if (liste_delete(l, 10, &nb_free) != 0) {
        printf("ERROR - CAS B tête\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    printf("OK CAS B\n");
    afficher_valeur(l);
    afficher_valeur(m);
    if (liste_delete(m, 10, &nb_free) != 0) {
        printf("ERROR - CAS C dernier\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    printf("OK CAS C\n");
    afficher_valeur(l);
    afficher_valeur(m);
    if (liste_delete(l, 10, &nb_free) != 1) {
        printf("ERROR - CAS D absente\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    printf("OK CAS D\n");
    afficher_valeur(l);
    afficher_valeur(m);
    if (liste_delete(l, 30, &nb_free) != 0) {
        printf("ERROR - CAS E1 vider\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    printf("OK CAS E1\n");
    afficher_valeur(l);
    afficher_valeur(m);
    if (liste_delete(l, 10, &nb_free) != 1) {
        printf("ERROR - CAS E2 vide\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    printf("OK CAS E2\n");
    afficher_valeur(l);
    afficher_valeur(m);
    if (liste_delete(NULL, 10, &nb_free) != 1) {
        printf("ERROR - CAS F NULL\n");
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    printf("OK CAS F\n");
    afficher_valeur(l);
    afficher_valeur(m);
    struct Noeud *test = liste_ajouter_fin(m, 30);
    if (test != NULL) {
        nb_free_compare++;
        if (liste_delete(m, 30, &nb_free) != 0) {
            printf("ERROR - CAS G doublon\n");
            liste_liberer(l, &nb_free);
            liste_liberer(m, &nb_free);
            return 1;
        }
    }
    printf("OK CAS G\n");
    afficher_valeur(l);
    afficher_valeur(m);

    
    if (verifier_liste(m, test_delete_m, 2) != 0) {
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    afficher_valeur(m);
    if (verifier_liste(l, test_delete_l, 0) != 0) {
        liste_liberer(l, &nb_free);
        liste_liberer(m, &nb_free);
        return 1;
    }
    afficher_valeur(l);

    liste_liberer(l, &nb_free);
    liste_liberer(m, &nb_free);
    printf("Nombre de free nb_free: %zu nb_free_compare:%zu\n", nb_free, nb_free_compare);
    if (nb_free != nb_free_compare) {
        printf("free compare it's WRONG!\n");
        return 1;
    }
    else {
        printf("free compare it's OK!\n");
        return 0;
    }
}