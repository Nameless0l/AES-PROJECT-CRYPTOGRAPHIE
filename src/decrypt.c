#include "../include/decrypt.h"

extern const Byte rsbox[256];

// Main function which decrypt the message
void aesDecrypt(Byte *expandedKey, Byte *input, Byte *output){
    // The work is done on the output variable
	memcpy(output, input, SIZE_16);
    
    // First XOR with the key before launching the AES's inverted rounds
    addRoundKey(expandedKey + SIZE_16 * NROUNDS, output);
    
    // The NROUNDS - 1 first inverted rounds are identical
    for(int i = NROUNDS - 1; i > 0; i--)
    	aes_invRound(output, expandedKey + SIZE_16 * i);
	
	// The last round does not implement the inverse of mixcolumns function
	final_invRound(output, expandedKey);
}

// Represents a AES's inverted round
void aes_invRound(Byte *input, Byte *key){
	invShiftRows(input);
    invSubBytes(input);
    addRoundKey(key, input);
    invMixColumns(input);
}

// Represents the inverted AES's final round
void final_invRound(Byte *input, Byte *key){
	invShiftRows(input);
    invSubBytes(input);
    addRoundKey(key, input);
}

// Shifts to right a row by 1
void invShiftRows(Byte* state) {
	for(int nShift = 0; nShift < 4; nShift++)
    	invShiftRow(state + nShift * 4, nShift);
}

// Shifts to the right the lines of the state successively by 0, 1, 2 and 3
void invShiftRow(Byte *row, int nShift){
	for (int n = 0; n < nShift; n++) {
		Byte b = row[3];
		memcpy(row + 1, row, 3);
		row[0] = b;
	}
}

// Replaces all the values of the state by theirs correspondings in the sbox
void invSubBytes(Byte* state) {
  for (int i = 0; i < SIZE_16; i++)
    state[i] = rsbox[state[i]];
}

// Applys a multiplication of the state and the inverted C AES's matrix in the Galois corps
void invMixColumns(Byte* state) {
	execMixColumns(state, (Byte[]){0x0E, 0x0B, 0x0D, 0x09});
}

