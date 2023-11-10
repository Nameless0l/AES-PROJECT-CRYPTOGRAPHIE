#include "common.h"

extern const Byte sbox[256];
extern const Byte Rcon[255];

// Execute mixcolums corresponding to the mixcol_table given
// Either for the normal execution (encryption) or inverted (decryption)
void execMixColumns(Byte* state, Byte *mixcol_table) {	
  	int i, j, mixcol_i;
  
  	for (i = 0; i < 4; i++) {
	  	Byte col[4];
	  	
	  	for(j = 0; j < 4; j++)
	  		col[j] = state[j * 4 + i];
	  		
	  	for(j = 0; j < 4; j++){
	  		state[j * 4 + i] = 0;
	  		
	  		// Xoring successively the values for each column
		  	for(mixcol_i = 0; mixcol_i < 4; mixcol_i++)
				state[j * 4 + i] ^= gfMult(mixcol_table[(mixcol_i - j + 4) % 4], col[mixcol_i]);
		}
	}
}

// Generation of the NROUNDS keys
void keyExpansion(const Byte *cipherKey, Byte *expandedKey) {
	int i;
	int bytesGenerated = SIZE_16;
    int rconIteration = 1;
    Byte tmp[4];
    
    memcpy(expandedKey, cipherKey, SIZE_16);

    while (bytesGenerated < (NROUNDS + 1) * SIZE_16) {
        for (i = 0; i < 4; i++)
            tmp[i] = expandedKey[i + bytesGenerated - 4];

        if (bytesGenerated % SIZE_16 == 0) {
        	shiftRow(tmp, 1);
            
            for (i = 0; i < 4; i++)
                tmp[i] = sbox[tmp[i]];

            tmp[0] ^= Rcon[rconIteration++];
        }


        for (i = 0; i < 4; i++) {
            expandedKey[bytesGenerated] = expandedKey[bytesGenerated - SIZE_16] ^ tmp[i];
            bytesGenerated++;
        }
    }
}

/* For a expected matrix :
	[a0,0 a0,1 a0,2 a0,3]
	[a1,0 a1,1 a1,2 a1,3]
	[a2,0 a2,1 a2,2 a2,3]
	[a3,0 a3,1 a3,2 a3,3]

 *The clear text given is filled into following the order a0,0 a1,0 a2,0 a3,0 a0,1... a2,3 a3,3
 * It is the role of the following function. It returns that matrix (table) filled
**/
Byte *createInput(Byte *input){
	Byte *new_input = (Byte*)malloc(SIZE_16 * sizeof(Byte));
	
    int i, j;
	for (i = 0; i < 4; i++)
	    for (j = 0; j < 4; j++)
	        new_input[(i + (j * 4))] = (Byte)input[(i * 4) + j];
	        
	return new_input;
}	

// XOR the key and the input
void addRoundKey(Byte* cipherKey, Byte* input) {
	cipherKey = createInput(cipherKey);
    
    for (int i = 0; i < SIZE_16; i++)
        input[i] ^= cipherKey[i];
}

// Multiply the bytes a and b in the Galois corps
Byte gfMult(Byte b, Byte a) {
  Byte result = 0;

  while (b > 0) {
    if (b & 1)
		result ^= a;

	// 0x1b : Irreducible Polynôme of Galois in 2^8 : GF(2^8)
    a = (a << 1) ^ ((a & 0x80) ? 0x1b : 0);
    b >>= 1;
  }

  return result;
}

// Display as a matrix the bytes contained by "string" in hexadecimal and character modes
void printBytes(char *string, Byte *text){
	printf("%s :\n", string);
	
    for(int i = 0; i < SIZE_16; i++)
        printf("%02X(%c)%c",text[i], text[i], (i + 1) % 4 ? ' ' : '\n');
        
    printf("\n");
}
