#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

/* Contains Encryption principal functions */

#include "data.h"

void aesEncrypt(Byte *expandedKey, Byte *input, Byte *output);

void aes_round(Byte *input, Byte *key);
void subBytes(Byte* state);
void shiftRow(Byte *row, int nShift);
void shiftRows(Byte* state);
void mixColumns(Byte* state);
void final_round(Byte *input, Byte *key);

#endif //__FUNCTIONS_HPP__
