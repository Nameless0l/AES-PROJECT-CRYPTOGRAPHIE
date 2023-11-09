#include "functions.h"

extern const Byte sbox[256];
extern const Byte rsbox[256];
extern const Byte Rcon[255];

void keyExpansion(const Byte *cipherKey, Byte *expandedKey) {
	int i;
	int bytesGenerated = SIZE_16;
    int rconIteration = 1;
    Byte tmp[4];
	
    for (i = 0; i < SIZE_16; i++)
        expandedKey[i] = cipherKey[i];

    while (bytesGenerated < 176) {
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

void shiftRow(Byte *row, int nShift){
	for (int n = 0; n < nShift; n++) {
		Byte b = row[0];
		
		for(int i = 0; i < 4; i++)
			row[i] = row[i + 1];
		
		row[3] = b;
	}
}

void subBytes(Byte* state) {
  for (int i = 0; i < SIZE_16; i++)
    state[i] = sbox[state[i]];
}

void addRoundKey(Byte* cipherkey, Byte* input) {
	Byte *roundKey = malloc(SIZE_16 * sizeof(Byte));
	
	createInput(cipherkey, roundKey);
    
    for (int i = 0; i < SIZE_16; i++)
        input[i] ^= roundKey[i];
}

void shiftRows(Byte* state) {
	for(int nShift = 0; nShift < 4; nShift++)
    	shiftRow(state + nShift * 4, nShift);
}

Byte gfMult(Byte b, Byte a) {
  Byte result = 0;

  while (b > 0) {
    if (b & 1)
		result ^= a;

    a = (a << 1) ^ ((a & 0x80) ? 0x1b : 0);
    b >>= 1;
  }

  return result;
}

void mixColumns(Byte* state) {
  Byte MIXCOL_MATRIX[4] = {0x02, 0x03, 0x01, 0x01};

  int i, j;

  for (i = 0; i < 4; i++) {
  	Byte col[4];
  	
  	for(j = 0; j < 4; j++)
  		col[j] = state[j * 4 + i];
  	
	for(j = 0; j < 4; j++){
		state[j * 4 + i] = 0;
		
		for(int row_id = 0; row_id < 4; row_id++)
			state[j * 4 + i] ^= gfMult(MIXCOL_MATRIX[(row_id - j + 4) % 4], col[row_id]);
	}
  }
}

void *createInput(char *text, Byte *input){
    int i, j;
	for (i = 0; i < 4; i++)
	    for (j = 0; j < 4; j++)
	        input[(i + (j * 4))] = (Byte)text[(i * 4) + j];
}	    

void aesEncrypt(Byte *key, Byte *input, Byte *output){
    Byte expandedKey[176];
    keyExpansion(key, expandedKey);
    
    Byte *bytes = malloc(SIZE_16 * sizeof(Byte));
    memcpy(bytes, input, SIZE_16);
    
    addRoundKey(&expandedKey[0], bytes);
    
    for(int i = 1; i < NROUNDS; i++){
        subBytes(bytes);
        shiftRows(bytes);
        mixColumns(bytes);
        addRoundKey(expandedKey + SIZE_16 * i, bytes);
    }

    subBytes(bytes);
    shiftRows(bytes);
    addRoundKey(expandedKey + SIZE_16 * NROUNDS, bytes);
    
    memcpy(output, bytes, SIZE_16);
}

void printBytes(char *string, Byte *text){
	printf("%s :\n", string);
	
    for(int i = 0; i < SIZE_16; i++)
        printf("%02X%c",text[i], (i + 1) % 4 ? ' ' : '\n');
        
    printf("\n");
}
