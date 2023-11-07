#include <stdio.h>
#include <stdint.h>
#include<stdlib.h>
#include <string.h>

static const uint8_t sbox[256] =   {
  //0     1    2      3     4    5       6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };


static const uint8_t rsbox[256] =
{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };




// The round constant word array, Rcon[i], contains the values given by 
// x to th e power (i-1) being powers of x (x is denoted as {02}) in the field GF(2^8)
// Note that i starts at 1, not 0).
static const uint8_t Rcon[255] = {
  0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
  0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
  0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
  0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
  0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
  0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
  0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
  0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
  0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
  0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
  0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
  0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
  0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
  0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
  0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
  0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };

//begin of key expand

uint8_t* stringToBytes(char* string) {

  // Trouver la longueur de la chaîne
  int len = strlen(string);

  // Allouer un tableau pour contenir les octets
  uint8_t* bytes =malloc(len*sizeof(uint8_t));

  // Parcourir chaque caractère 
  int i;
  for(i=0; i<len; i++) {

    // Convertir le caractère en uint8_t et le stocker
    bytes[i] = (uint8_t)string[i]; 
  }

  return bytes;

}
void keyExpansion(const uint8_t *cipherKey, uint8_t *expandedKey) {
    for (int i = 0; i < 16; i++) {
        expandedKey[i] = cipherKey[i];
    }

    int bytesGenerated = 16;
    int rconIteration = 1;
    uint8_t temp[4];

    while (bytesGenerated < 176) {
        for (int i = 0; i < 4; i++) {
            temp[i] = expandedKey[i + bytesGenerated - 4];
        }

        if (bytesGenerated % 16 == 0) {
            uint8_t t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;

            for (int i = 0; i < 4; i++) {
                temp[i] = sbox[temp[i]];
            }

            temp[0] = temp[0] ^ Rcon[rconIteration];
            rconIteration++;
        }

        for (unsigned int i = 0; i < 4; i++) {
            expandedKey[bytesGenerated] = expandedKey[bytesGenerated - 16] ^ temp[i];
            bytesGenerated++;
        }
    }
}

void SubBytes(uint8_t* state) {

  int i;

  // Itérer sur chaque octet du state
  for(i=0; i<16; i++) {

    // Utiliser la valeur de l'octet comme index pour la Sbox 
    state[i] = sbox[state[i]];

  }

}

uint8_t hexToBin(uint8_t hex) {

  uint8_t bin = 0;

  // Itérer sur chaque digit hex 
  for (int i = 0; i < 2; i++) {

    // Extraire le digit courant
    uint8_t digit = (hex >> (4 * (1 - i))) & 0xF;

    // Convertir en binaire
    if (digit >= 0 && digit <= 9) {
      bin |= (digit << (4 * i)); 
    }
    else if (digit >= 0xA && digit <= 0xF) {
      bin |= ((digit - 0xA + 10) << (4 * i));
    }
  }

  return bin;

}

uint8_t xorBytes(uint8_t byte1, uint8_t byte2) {

  uint8_t result = 0;

  for (int i = 0; i < 16; i++) {

    // Extraire les bits 
    uint8_t bit1 = (byte1 >> i) & 1; 
    uint8_t bit2 = (byte2 >> i) & 1;

    // Faire le XOR
    uint8_t xorBit = bit1 ^ bit2;

    // Mettre le bit résultat dans le résultat
    result |= (xorBit << i); 
  }

  return result;

}

uint8_t binToHex(uint8_t bin) {
  
  uint8_t hex = 0;

  // Itérer sur chaque groupe de 4 bits
  for (int i = 0; i < 2; i++) {

    // Extraire les 4 bits
    uint8_t nibble = (bin >> (4 * (1 - i))) & 0xF;

    // Convertir en hex 
    if (nibble >= 0 && nibble <= 9) {
      hex |= (nibble << (4 * i));
    } else if (nibble >= 0xA && nibble <= 0xF) {
      hex |= ((nibble - 0xA + 10) << (4 * i)); 
    }
  }

  return hex;

}
// Prend deux tableaux d'octets hexadécimaux
uint8_t* xorHexBytes(uint8_t* hex1, uint8_t* hex2, int len) {

  // Allouer le tableau résultat
  uint8_t* result = malloc(len);

  // Parcourir chaque paire d'octets
  for (int i = 0; i < len; i++) {

    // Convertir les octets hex en binaire 
    uint8_t byte1 = hexToBin(hex1[i]);
    uint8_t byte2 = hexToBin(hex2[i]); 

    // Faire le XOR binaire
    uint8_t xored = xorBytes(byte1, byte2);

    // Convertir le résultat xor en hex
    result[i] = binToHex(xored);
  }

  return result;

}


void shiftRows(uint8_t* state) {

  uint8_t temp;

  // Décalage sur la première ligne
  temp = state[1];
  state[1] = state[5];
  state[5] = state[9];
  state[9] = state[13];
  state[13] = temp;

  // Décalage sur la deuxième ligne
  temp = state[2];
  state[2] = state[10];
  state[10] = temp;
  temp = state[6];
  state[6] = state[14];
  state[14] = temp;

  // Décalage sur la troisième ligne
  temp = state[15];
  state[15] = state[11];
  state[11] = state[7];
  state[7] = state[3];
  state[3] = temp;

}

//MIX co;umn

// Matrice de multiplication dans GF(2^8)
// Matrice de multiplication dans GF(2^8)
const uint8_t mixColMatrix[4][4] = {
  {0x02, 0x03, 0x01, 0x01},
  {0x01, 0x02, 0x03, 0x01},
  {0x01, 0x01, 0x02, 0x03},
  {0x03, 0x01, 0x01, 0x02}
};

// Polynôme irréductible pour GF(2^8) 
#define AES_POLY 0x1b

uint8_t gfMult(uint8_t a, uint8_t b) {
  uint8_t result = 0; 

  while (b > 0) {
    // Si b est impair, ajouter a à result
    if (b & 1) {
      result ^= a; 
    }

    // Doubler a dans GF(2^8)
    a = (a << 1) ^ ((a & 0x80) ? AES_POLY : 0);

    // Diviser b par 2
    b >>= 1; 
  }

  return result;
}

// Matrice de mixage  
void mixColumns(uint8_t* state) {
  uint8_t temp[16];

  // Copier state dans temp
  for (int i = 0; i < 16; i++) {
    temp[i] = state[i];
  }

  // Iterer sur les colonnes
  for (int i = 0; i < 4; i++) {
    // Initialiser la colonne temporaire
    uint8_t t0 = temp[i];
    uint8_t t1 = temp[4+i];
    uint8_t t2 = temp[8+i]; 
    uint8_t t3 = temp[12+i];

    // Calculer la nouvelle colonne
    state[i] = gfMult(0x02, t0) ^ gfMult(0x03, t1) ^  
              gfMult(0x01, t2) ^ gfMult(0x01, t3);

    state[4+i] = gfMult(0x01, t0) ^ gfMult(0x02, t1) ^ 
                gfMult(0x03, t2) ^ gfMult(0x01, t3);

    state[8+i] = gfMult(0x01, t0) ^ gfMult(0x01, t1) ^
                gfMult(0x02, t2) ^ gfMult(0x03, t3);

    state[12+i] = gfMult(0x03, t0) ^ gfMult(0x01, t1) ^ 
                 gfMult(0x01, t2) ^ gfMult(0x02, t3);
  }
}

int main() {

    char* string = "MESSAGEENCRPTION";
    uint8_t* bytes = stringToBytes(string);
    uint8_t plain_text [16]={'M','E' ,'S','S','A','G','E','E','N','C','R','P','T','I','O','N'};
    uint8_t cipherKey[16] = {'T', 'E', 'A', 'M', 'S', 'C', 'O', 'R', 'P', 'I', 'A', 'N', '1', '2', '3', '4'};
    uint8_t expandedKey[176];
    keyExpansion(cipherKey, expandedKey);
    uint8_t *xor= xorHexBytes(expandedKey , bytes,16);
    SubBytes(xor);
    shiftRows(xor);
    mixColumns(xor);
    
    for (int i = 0 ; i<strlen(string);i++)
    {
        // printf("%02X ", xor[i]);
        printf("%c ", (char)xor[i]);
    }

    // printf("Expanded Key: ");
    // for (int i = 0; i < 176; i++) {
    //     printf("%02X ", expandedKey[i]);
    // }
    printf("\n");

    return 0;
}