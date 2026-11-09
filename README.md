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

Chaque structure est séparée en bibliothèque et programme de test. `make` construit les deux programmes.

**Tableau d'entiers dynamique** (fait) :

- `tableau.h` : la structure et les déclarations ;
- `tableau.c` : création, ajout en fin (capacité doublée avec `realloc`, tableau intact si l'agrandissement
  échoue), lecture avec vérification des bornes, libération ;
- `main_tableau.c` : 1000 ajouts depuis une capacité de 0, puis chaque valeur relue et comparée à la valeur
  attendue.

```
cd 02-structures
make
.\dist\tableau.exe
echo $LASTEXITCODE
```

```
taille=1000 - capacite=1024
OK : 1000 valeurs verifiees.
0
```

Le test renvoie 1 et affiche la première erreur (indice, valeur attendue, valeur lue) si une valeur est fausse.

**Liste chaînée** (en cours) :

- `liste.h` : un nœud (valeur et adresse du suivant) et la liste (premier nœud et taille) ;
- `liste.c` : création d'une liste vide, ajout en tête (renvoie `NULL` si l'allocation échoue, liste intacte),
  affichage, lecture du n-ième élément avec vérification de l'indice (valeur rendue par pointeur, rien n'est
  écrit en cas de refus), libération qui accepte `NULL` (pour l'instant, la structure seulement, pas les nœuds) ;
- `main_liste.c` : ajout en tête de 30, 20 puis 10, puis vérification de la taille, de l'ordre des valeurs
  (la liste se lit 10, 20, 30 : l'ajout en tête inverse l'ordre) et de la fin de la chaîne ; lecture des indices 0 à 2, puis refus de l'indice 3 et d'une liste vide, avec
  la variable de sortie inchangée.

```
cd 02-structures
make
.\dist\liste.exe
echo $LASTEXITCODE
```

```
...
TAILLE OK!
valeur:10 valeur:20 valeur:30
last P value is NULL
VALEUR OK!
test 1 -- buffer:10 - valeur_ajouts:10
test 1 -- buffer:20 - valeur_ajouts:20
test 1 -- buffer:30 - valeur_ajouts:30
test 2 -- buffer:777
test 3 -- buffer:777
0
```

Chaque vérification ratée affiche une ligne `ERROR` et le test renvoie 1.

Viendront ensuite la libération de tous les nœuds, l'ajout en fin et la suppression. La table de hachage suivra
dans le même dossier.

`make clean` supprime les fichiers compilés.

## Cadre

Les outils de reverse et de modding visent mes propres programmes et des jeux solo hors ligne, sans anti-triche.
Les pilotes noyau se testent uniquement dans une machine virtuelle.

## Licence

[Apache 2.0](LICENSE)
