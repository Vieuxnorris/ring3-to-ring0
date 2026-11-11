#include "liste.h"
#include <stdio.h>

enum {MAX_INDEX=3};

int main(void) {

    int ajouts[] = {30,20,10};
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
        n = liste_ajouter_tete(l,ajouts[i]);
        if (n == NULL) {
            printf("ERROR ALLOC Noeud 1\n");
            liste_liberer(l, &nb_free);
            return 1;
        }
        printf("taille:%zu - adresse:0x%p\n", l->taille, l->premier);
        nb_free_compare++;
    }
    if (l->taille != 3) {
        printf("ERROR TAILLE Liste l->taille:%zu attendu:%d\n", l->taille, MAX_INDEX);
        liste_liberer(l, &nb_free);
        return 1;
    }
    printf("TAILLE OK!\n");

    afficher_valeur(l);

    // test Valeurs
    struct Noeud *p = l->premier;
    size_t index = 0;
    while (p != NULL && index != MAX_INDEX) {
        if (ajouts[(MAX_INDEX-1) - index] != p->valeur) {
            printf("ERROR p->valeur non conforme index:%zu index_value:%d valeur_p:%d\n", index, ajouts[(MAX_INDEX-1) - index],p->valeur);
            liste_liberer(l, &nb_free);
            return 1;
        }
        index++;
        p = p->suivant;
    }

    // Test last P
    if (p != NULL) {
        liste_liberer(l, &nb_free);
        return 1;
    }
    printf("last P value is NULL\n");

    // test index test
    if (index != MAX_INDEX) {
        printf("ERROR INDEX MAX - index_valeur:%zu max_index:%d\n", index, MAX_INDEX);
        liste_liberer(l, &nb_free);
        return 1;
    }
    printf("VALEUR OK!\n");

    for (size_t i=0; i<3;i++) {
        int buffer = 777;
        if(liste_lire(l, i, &buffer) == 0) {
            if(buffer == ajouts[(MAX_INDEX-1) - i]) {
                printf("test 1 -- buffer:%d - valeur_ajouts:%d\n", buffer, ajouts[(MAX_INDEX - 1) - i]);
            } else {
                printf("ERROR test 1 -- buffer:%d - valeur_ajouts:%d\n", buffer, ajouts[(MAX_INDEX - 1) - i]);
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