#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        FILE *f = fopen(argv[1], "rb");

        if (f == NULL) {
            printf("impossible d'ouvrir le fichier\n");
            return 1;
        }

        unsigned char buffer[16];
        size_t lus = fread(buffer, 1, sizeof(buffer), f);

        size_t offset = 0;        
        while (lus > 0) {
            printf("%08zx ", offset);
            for (size_t i=0; i < lus; i++) {
                printf("%02x ", *(buffer + i));
                offset++;
            }
            for (size_t i=lus; i < sizeof(buffer); i++) {
                printf("   ");
            }
            for (size_t i=0; i < lus; i++) {
                unsigned char c = *(buffer + i);
                if (c >= 0x20 && c <= 0x7e) {
                    printf("%c", c);
                }
                else {
                    printf(".");
                }
            }
            printf("\n");
            lus = fread(buffer, 1, sizeof(buffer), f);
        }

        fclose(f);
        return 0;
    }
    printf("usage: hexdump <fichier>\n");
    return 1;
}