#ifndef __DECRYPT_H__
#define __DECRYPT_H__

/* Contains Decryption principal functions */

#include "data.h"

void aesDecrypt(Byte *expandedKey, Byte *input, OUT Byte *output);

void aes_invRound(Byte *input, Byte *key);
void invSubBytes(HYB Byte* state);
void invShiftRows(HYB Byte* state);
void invShiftRow(HYB Byte *row, int nShift);
void invMixColumns(HYB Byte* state);
void final_invRound(HYB Byte *input, Byte *key);
	
#endif //__DECRYPT_H__
