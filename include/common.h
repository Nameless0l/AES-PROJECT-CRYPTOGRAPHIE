#ifndef __COMMON_HPP__
#define __COMMON_HPP__

/* Contains functions common to encryption and decryption */

#include "data.h"

Byte gfMult(Byte b, Byte a);
void printBytes(char *string, Byte *text);
void keyExpansion(const Byte *cipherKey, Byte *expandedKey);
Byte *createInput(Byte *input);
void addRoundKey(Byte* cipherKey, Byte* input);
void execMixColumns(Byte* state, Byte *mixcol_table);

#endif //__COMMON_HPP__
