#include "../include/encrypt.h"

extern const Byte sbox[256];

// Main function which encrypt the message
void aesEncrypt(Byte *expandedKey, Byte *input, Byte *output){
    // The work is done on the output variable
    memcpy(output, createInput(input), 16);
    
    // First XOR with the key before launching the AES's rounds
    addRoundKey(expandedKey, output);
    
    // The NROUNDS - 1 first rounds are identical
    for(int i = 1; i < NROUNDS; i++)
    	aes_round(output, expandedKey + SIZE_16 * i);

	// The last round does not implement the mixcolumns function
	final_round(output, expandedKey + SIZE_16 * NROUNDS);
}

// Represents a AES's round
void aes_round(Byte *input, Byte *key){
	subBytes(input);
	shiftRows(input);
	mixColumns(input);
    addRoundKey(key, input);
}

// Represents the AES's final round
void final_round(Byte *input, Byte *key){
    subBytes(input);
    shiftRows(input);
    addRoundKey(key, input);
}

// Shifts to the left a row by 1
void shiftRow(Byte *row, int nShift){
	for (int n = 0; n < nShift; n++) {
		Byte b = row[0];
		memcpy(row, row + 1, 3);
		row[3] = b;
	}
}

// Shifts to the left the lines of the state successively by 0, 1, 2 and 3
void shiftRows(Byte* state) {
	for(int nShift = 0; nShift < 4; nShift++)
    	shiftRow(state + nShift * 4, nShift);
}

// Replaces all the values of the state by theirs correspondings in the sbox
void subBytes(Byte* state) {
  for (int i = 0; i < SIZE_16; i++)
    state[i] = sbox[state[i]];
}

// Applys a multiplication of the state and the C AES's matrix in the Galois corps
void mixColumns(Byte* state) {
	execMixColumns(state, (Byte[]){0x02, 0x03, 0x01, 0x01});
}

