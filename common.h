#ifndef __COMMON_H__
#define __COMMON_H__

/* Contains functions common to encryption and decryption */

#include "data.h"

typedef uint8_t Byte;

void aesMain(Byte expandedKey[(NROUNDS + 1) * SIZE_16], Byte *input, Byte nBlock, OUT Byte *encOutput, OUT Byte *decOutput);

Byte gfMult(Byte b, Byte a);
void printBytes(char *string, Byte *text, int size);
void keyExpansion(const Byte *cipherKey, OUT Byte *expandedKey);
Byte *transpose(HYB Byte *input, int nBlock);
void addRoundKey(Byte* key, HYB Byte* input);
void execMixColumns(HYB Byte* state, Byte *mixcol_table);
Byte *readEntry(char *s, int *inputLength, int *nBlock);
int randomInteger(int a, int b);
void printDecorationLine(int n);
int getNBlock(int bytes);

#endif //__COMMON_H__
