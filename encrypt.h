#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/* Contains Encryption principal functions */

#include "data.h"

typedef uint8_t Byte;

void aesEncrypt(Byte *expandedKey, Byte *input, OUT Byte *output);

void aes_round(HYB Byte *input, Byte *key);
void subBytes(HYB Byte* state);
void shiftRow(HYB Byte *row, int nShift);
void shiftRows(HYB Byte* state);
void mixColumns(HYB Byte* state);
void final_round(HYB Byte *input, Byte *key);

#endif //__FUNCTIONS_H__
