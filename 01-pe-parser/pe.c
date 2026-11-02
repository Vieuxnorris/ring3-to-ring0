#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE *f = fopen(argv[1], "rb");

        if (f == NULL) {
            printf("impossible d'ouvrir le fichier\n");
            return 1;
        }
        uint32_t n;
        uint32_t signature;
        uint16_t machine;
        uint16_t NumberOfSection;

        // n
        fseek(f, 0x3c, SEEK_SET);
        size_t lus = fread(&n, sizeof(n), 1, f);
        if (lus != 1) {
            printf("Erreur read PE\n");
            fclose(f);
            return 1;
        }
        // signature
        fseek(f, n, SEEK_SET);
        lus = fread(&signature, sizeof(signature), 1, f);
        if (lus != 1 || signature != 0x4550) {
            printf("pas un fichier PE\n");
            fclose(f);
            return 1;
        }
        else {
            printf("fichier PE valide\n");
        }
        // machine
        lus = fread(&machine, sizeof(machine), 1, f);
        if (lus != 1) {
            printf("pas de code Machine\n");
            fclose(f);
            return 1;
        } else {
            printf("Machine: 0x%04x\n", machine);
        }
        // Number Of Section
        lus = fread(&NumberOfSection, sizeof(NumberOfSection), 1, f);
        if (lus != 1) {
            printf("pas de code section\n");
            fclose(f);
            return 1;
        } else {
            printf("Section: %u\n", NumberOfSection);
        }

        fclose(f);
        return 0;
    }
    printf("usage: pe <fichier>\n");
    return 1;
}