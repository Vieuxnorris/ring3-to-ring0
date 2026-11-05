# ring3-to-ring0

Apprendre le C, le C++ et l'assembleur x86-64 en écrivant de vrais outils, du premier octet lu dans un fichier
jusqu'au noyau.

## Projets

| #  | Projet                                                                                 | Langage | État |
|----|----------------------------------------------------------------------------------------|---------|------|
| 01 | [Analyseur PE](01-pe-parser) : hexdump, en-tête COFF et noms des sections d'un `.exe` Windows | C       | fait |
| 02 | Bibliothèque de structures : tableau dynamique, liste chaînée, table de hachage           | C       | en cours |

## Parcours

1. **Bases du C** : formats binaires, structures de données, allocateur, compression, SHA-256.
2. **La machine** : assembleur x86-64, émulateurs, désassembleur, mini-compilateur, chargeur de `.exe`.
3. **C++** : RAII, templates, moteur de jeu, réseau, concurrence.
4. **Windows et reverse** : processus, mémoire, débogueur, hooks, crackmes.
5. **Modding de jeux solo** : trainers, formats de fichiers, mods par DLL.
6. **Noyau** : mini-noyau, pilotes Windows, hyperviseur.

## Compiler

Prérequis : `gcc` (MinGW-w64, par exemple via MSYS2) et GNU Make.

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

`make clean` supprime les fichiers compilés.

## Cadre

Les outils de reverse et de modding visent mes propres programmes et des jeux solo hors ligne, sans anti-triche.
Les pilotes noyau se testent uniquement dans une machine virtuelle.

## Licence

[Apache 2.0](LICENSE)
