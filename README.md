# ring3-to-ring0

Apprendre le C, le C++ et l'assembleur x86-64 en écrivant de vrais outils, du premier octet lu dans un fichier
jusqu'au noyau.

## Projets

| #  | Projet                                                                                 | Langage | État |
|----|----------------------------------------------------------------------------------------|---------|------|
| 01 | [Analyseur PE](01-pe-parser) : hexdump, en-tête COFF et noms des sections d'un `.exe` Windows | C       | fait |
| 02 | [Bibliothèque de structures](02-structures) : tableau dynamique, liste chaînée, table de hachage | C       | en cours |

## Parcours

1. **Bases du C** : formats binaires, structures de données, allocateur, compression, SHA-256.
2. **La machine** : assembleur x86-64, émulateurs, désassembleur, mini-compilateur, chargeur de `.exe`,
   bootloader et mini-noyau.
3. **C++** : RAII, templates, moteur de jeu, réseau, concurrence.
4. **Windows et reverse** : processus, mémoire, débogueur, hooks, crackmes.
5. **Modding de jeux solo** : trainers, formats de fichiers, mods par DLL.
6. **Noyau Windows** : pilotes, hyperviseur.

## Compiler

Prérequis : `gcc` (MinGW-w64, par exemple via MSYS2) et GNU Make. Chaque projet a son propre Makefile et compile
dans son dossier `dist/`.

### 01 : analyseur PE

```
cd 01-pe-parser
make
.\dist\pe.exe C:\Windows\System32\notepad.exe
```

```
fichier PE valide
Machine              : 0x8664
NumberOfSection      : 8
TimeDateStamp        : 288297124
PointerToSymbolTable : 0
NumberOfSymbols      : 0
SizeOfOptionalHeader : 0xf0
Characteristics      : 34
.text
fothk
.rdata
...
```

### 02 : bibliothèque de structures

Chaque structure est séparée en bibliothèque et programme de test. `make` construit les trois programmes.

**Tableau d'entiers dynamique** (fait) :

- `array.h` : la structure et les déclarations ;
- `array.c` : création, ajout en fin (capacité doublée avec `realloc`, tableau intact si l'agrandissement
  échoue), lecture avec vérification des bornes, libération ;
- `main_array.c` : 1000 ajouts depuis une capacité de 0, puis chaque valeur relue et comparée à la valeur
  attendue.

```
cd 02-structures
make
.\dist\array.exe
echo $LASTEXITCODE
```

```
size=1000 - capacity=1024
OK: 1000 values checked.
0
```

Le test renvoie 1 et affiche la première erreur (indice, valeur attendue, valeur lue) si une valeur est fausse.

**Liste chaînée** (fait) :

- `list.h` : un nœud (valeur et adresse du suivant) et la liste (premier nœud et taille) ;
- `list.c` : création d'une liste vide, ajout en tête et ajout en fin (renvoient `NULL` si l'allocation
  échoue, liste intacte), affichage, lecture du n-ième élément avec vérification de l'indice (valeur rendue
  par pointeur, rien n'est écrit en cas de refus), suppression de la première occurrence d'une valeur
  (renvoie 1 si elle est absente), libération de tous les nœuds puis de la liste, qui accepte `NULL` ; la
  suppression et la libération peuvent compter leurs `free` dans un compteur passé par adresse (`NULL` si
  l'appelant ne compte pas) ;
- `main_list.c` : ajout en tête de 30, 20 puis 10 (la liste se lit 10, 20, 30 : l'ajout en tête inverse
  l'ordre), vérification de la taille, de l'ordre des valeurs et de la fin de la chaîne ; lecture des
  indices 0 à 2, puis refus de l'indice 3 et d'une liste vide, avec la variable de sortie inchangée ; ajouts
  en fin, dont un échec d'allocation forcé qui doit laisser la liste intacte ; suppressions en tête, au
  milieu, en fin, d'une valeur absente, du dernier élément, dans une liste vide, dans une liste `NULL` et
  d'une valeur en double (seul le premier exemplaire part), chacune vérifiée par son retour, puis par
  l'ordre et la taille de la liste ; enfin, le nombre de `free` faits est comparé au nombre d'allocations
  comptées par le test (1 par liste créée, 1 par nœud ajouté).

```
cd 02-structures
make
.\dist\list.exe
echo $LASTEXITCODE
```

```
...
OK CASE F

value:30 value:20
OK CASE G
...
Number of free nb_free: 12 nb_free_compare:12
free compare it's OK!
0
```

Chaque vérification ratée affiche une ligne `ERROR` (ou `WRONG` pour le compte des `free`) et le test
renvoie 1. Par exemple, si `list_free` oublie de libérer la structure de la liste, le test affiche
`nb_free: 9 nb_free_compare:12` et renvoie 1.

**Table de hachage** (en cours) : clés et valeurs `int`, une liste chaînée par case pour les clés qui
tombent dans la même case.

- `hash.h` : une entrée (clé, valeur, adresse de la suivante) et la table (tableau de cases, nombre de
  cases, nombre de clés) ;
- `hash.c` : création avec toutes les cases vides (refuse 0 case, et rend ce qu'elle a déjà alloué si une
  allocation échoue), libération des entrées de chaque case, puis du tableau de cases et de la table, avec
  le même compteur de `free` que la liste ;
- `main_hash.c` : création et libération d'une table de 10 cases (2 `free` attendus), refus d'une table de
  0 case et d'une table trop grande pour être allouée.

```
cd 02-structures
make
.\dist\hash.exe
echo $LASTEXITCODE
```

```
ERROR NB_BUCKETS: 0
ERROR MALLOC ENTRY LIST
Number of free nb_free: 2 nb_free_compare:2
free compare it's OK!
0
```

Les deux lignes `ERROR` viennent des deux refus attendus. Viendront ensuite le calcul de la case d'une
clé (y compris négative), l'ajout, la lecture et la suppression d'une clé.

`make clean` supprime les fichiers compilés.

## Cadre

Les outils de reverse et de modding visent mes propres programmes et des jeux solo hors ligne, sans anti-triche.
Les pilotes noyau se testent uniquement dans une machine virtuelle.

## Licence

[Apache 2.0](LICENSE)
