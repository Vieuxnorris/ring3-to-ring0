#include <stdio.h>
#include <stdint.h>

#define ROUGE "\x1b[31m"
#define VERT "\x1b[32m"
#define RESET "\x1b[0m"

#define PE 0x3c
#define SIG 0x4550

struct Entete {
    uint16_t Machine; // + 0
    uint16_t NumberOfSection; // + 2
    uint32_t TimeDateStamp; // + 4
    uint32_t PointerToSymbolTable; // + 8
    uint32_t NumberOfSymbols; // + 12
    uint16_t SizeOfOptionalHeader; // + 16
    uint16_t Characteristics; // + 18
};

void afficher_entete(const struct Entete *e) {
    printf("Machine              : 0x%04x\n", e->Machine);
    printf("NumberOfSection      : %u\n", e->NumberOfSection);
    printf("TimeDateStamp        : %u\n", e->TimeDateStamp);
    printf("PointerToSymbolTable : %u\n", e->PointerToSymbolTable);
    printf("NumberOfSymbols      : %u\n", e->NumberOfSymbols);
    printf("SizeOfOptionalHeader : 0x%x\n", e->SizeOfOptionalHeader);
    printf("Characteristics      : %u\n", e->Characteristics);
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE *f = fopen(argv[1], "rb");

        if (f == NULL) {
            printf("impossible d'ouvrir le fichier\n");
            return 1;
        }

        uint32_t n;
        uint32_t signature;
        struct Entete e;

        // n
        fseek(f, PE, SEEK_SET);
        size_t lus = fread(&n, sizeof(n), 1, f); // NOTEPAD ON 'PE' : f8 00 00 00
        if (lus != 1) {
            printf(ROUGE "Erreur read PE" RESET "\n");
            fclose(f);
            return 1;
        }
        // signature
        fseek(f, n, SEEK_SET);
        lus = fread(&signature, sizeof(signature), 1, f); // 0x4550
        if (lus != 1 || signature != SIG) {
            printf(ROUGE "pas un fichier PE" RESET "\n");
            fclose(f);
            return 1;
        }
        else {
            printf(VERT "fichier PE valide" RESET "\n");
        }
        // Entete COFF
        lus = fread(&e, sizeof(e), 1, f); // 20 * 1 block
        if (lus != 1) {
            printf(ROUGE "COFF impossible" RESET "\n");
            fclose(f);
            return 1;
        }
        else {
            afficher_entete(&e);
        }

        fseek(f, e.SizeOfOptionalHeader, SEEK_CUR);
        unsigned char nom[9]; // +1 for \0

        for(size_t section=0; section < e.NumberOfSection; section++) {
            lus = fread(nom, sizeof(nom) - 1, 1, f);
            nom[8] = '\0';
            if (lus != 1) {
                printf(ROUGE "Invalid section" RESET "\n");
                fclose(f);
                return 1;
            } else {
                printf("%s\n", nom);
                fseek(f, 32, SEEK_CUR);
            }
        }
        fclose(f);
        return 0;
    }
    printf("usage: pe <fichier>\n");
    return 1;
}