#ifndef __DECRYPT_H__
#define __DECRYPT_H__

/* Contains Decryption principal functions */

#include "data.h"

void aesDecrypt(Byte *expandedKey, Byte *input, Byte *output);

void aes_invRound(Byte *input, Byte *key);
void invSubBytes(Byte* state);
void invShiftRows(Byte* state);
void invShiftRow(Byte *row, int nShift);
void invMixColumns(Byte* state);
void final_invRound(Byte *input, Byte *key);
	
#endif //__DECRYPT_H__
