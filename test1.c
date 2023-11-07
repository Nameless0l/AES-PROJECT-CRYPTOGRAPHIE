#include <stdio.h>

int main() {
    unsigned char tableau_hexa[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    int taille = sizeof(tableau_hexa) / sizeof(tableau_hexa[0]);

    printf("Tableau hexadécimal: ");
    for(int i = 0; i < taille; i++) {
        printf("%02X ", tableau_hexa[i]);
    }

    return 0;
}