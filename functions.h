#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_16 16
#define NROUNDS 10
#define BUF_SIZE 255

typedef uint8_t Byte;

void keyExpansion(const Byte *cipherKey, Byte *expandedKey);
void subBytes(Byte* state);
void addRoundKey(Byte* cipherkey, Byte* input);
void shiftRows(Byte* state);
Byte gfMult(Byte b, Byte a);
void mixColumns(Byte* state);
void aesEncrypt(Byte *key, Byte *input, Byte *output);
void *createInput(char *text, Byte *input);
void printBytes(char *string, Byte *text);
void shiftRow(Byte *row, int nShift);

#endif //__FUNCTIONS_HPP__
