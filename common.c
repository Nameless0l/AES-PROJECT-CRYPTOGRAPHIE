#include "common.h"

extern const Byte sbox[256];
extern const Byte Rcon[255];

// mixcol_table is a kind of table used to represent all the AES's C matrix 
// Execute mixcolums corresponding to the mixcol_table given
// Either for the normal execution (encryption) or inverted (decryption)
void execMixColumns(HYB Byte* state, Byte *mixcol_table) {
	// mixcol_i is used to browse the mixcol_table
  	int i, j, mixcol_i;
  
  	for (i = 0; i < 4; i++) {
	  	Byte col[4]; // Used to store each column of the state
	  	
	  	for(j = 0; j < 4; j++)
	  		col[j] = state[j * 4 + i];
	  		
	  	for(j = 0; j < 4; j++){
	  		state[j * 4 + i] = 0; // 0 is the neutral element of the addition (substration)
	  		
	  		// Xoring successively the values for each column
		  	for(mixcol_i = 0; mixcol_i < 4; mixcol_i++)
				state[j * 4 + i] ^= gfMult(mixcol_table[(mixcol_i - j + 4) % 4], col[mixcol_i]);
		}
	}
}

// Generation of the NROUNDS keys
void keyExpansion(const Byte *cipherKey, OUT Byte *expandedKey) {
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
Byte *transpose(Byte *input, int nBlock){
	Byte *new_input = (Byte*)malloc(nBlock * SIZE_16 * sizeof(Byte));
	
	int i, j, k;
	
	Byte *new_in = new_input;
			
	// Transpose successively all the block (16 bytes each) of the state : Columns become Rows and Rows become Columns
	for(k = 0; k < nBlock; k++){
		for (i = 0; i < 4; i++)
		    for (j = 0; j < 4; j++)
			new_in[(i + (j * 4))] = (Byte)input[(i * 4) + j];
			
		new_in += SIZE_16;
	}
	        
	return new_input;
}	

// XOR the key and the input
void addRoundKey(Byte* key, HYB Byte* input) {
	key = transpose(key, SIZE_16);

	// Xoring successively the values of input and the key    
    for (int i = 0; i < SIZE_16; i++)
        input[i] ^= key[i];
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

// Just print a decoration line like "+--+--+" for aesthetic
void printDecorationLine(int n){
	printf("+");
	for(int i = 0; i < n; i++)
		printf("--+");
		
	printf("\n");
}

// Display the characters codes and theirs hexadecimal correspondings of the text given
void printBytes(char *string, Byte *text, int size){
	const int BYTESPERLINE = SIZE_16;
	
	printf("%s:\n", string);
	
	size = getNBlock(size) * SIZE_16;
	
	for(int counter = 0; counter < size / BYTESPERLINE; counter++){
		printDecorationLine(BYTESPERLINE);
		printf("|");
		
		for(int i = 0; i < BYTESPERLINE; i++)
			printf("%02X|", text[counter * BYTESPERLINE + i]);
		
		printf("\n");
		printDecorationLine(BYTESPERLINE);
		printf("|");
			
		// Print normally characters between 0 and 255, but print '?' symbol for other values (This case should not occurs
		for(int i = 0; i < BYTESPERLINE; i++){
			char c = text[counter * BYTESPERLINE + i];
			printf("%2c|", c > 255 || c < 0 ? '?' : c);
		}
			
		printf("\n");
		printDecorationLine(BYTESPERLINE);
		printf("\n\n");
	}
}

// Return a random value between a and b excluded
int randomInteger(int a, int b){
	return (rand() % (b - a)) + a;
}

// Return the number of blocks corresponding the number of bytes "bytes"
int getNBlock(int bytes){
	return (int)ceil(bytes / (double)SIZE_16);
}

// Read the message entered and return a pointer on a memory space corresponding to the length of the text
// After that, the messsage is filled in columns order
Byte *readEntry(char *s, int *inputLength, int *nBlock){
	char *entry = malloc(SIZE_16 * sizeof(char));
	char c = 0;
	unsigned int i = 0;
	
	printf("%s", s);

	// We read characters and realloc a table only if the length of the msg crossed the lenght of the barrier given successively by the multiples of SIZE_16
	while((c = getchar()) != '\n'){
		entry[i++] = c;
		
		if(i % SIZE_16 == 0)
			entry = realloc(entry, i + SIZE_16);
	} // After the loop, i represents the length of the message;
	
	*inputLength = i;
	*nBlock = getNBlock(*inputLength); // Getting the number of blocks to encrypt
	
	// msgSize represents the number of bytes of the message including the non-filled bytes
	const int msgSize = *nBlock * SIZE_16;

	// Filling the rest of the message with random characters from the ASCII table in order to fit a multiple of 128 bytes
	if(*inputLength % SIZE_16)
		for(int j = *inputLength; j < msgSize; j++)
			entry[j] = randomInteger(1, 256);
	
	// Transpose the messsage
	entry = transpose(entry, *nBlock);
	
	return (Byte*)entry;
}

// Main function to treat encryption and decryption of the message following the AES principles
void aesMain(Byte expandedKey[(NROUNDS + 1) * SIZE_16], Byte *input, Byte nBlock, OUT Byte *encOutput, OUT Byte *decOutput){
	Byte *inP = input;
	Byte *encP = encOutput;
	Byte *decP = decOutput;

	// Working successively on the differents blocks (128 bits = 16 bytes each) of the input
	for(int i = 1; i <= nBlock; i++){
		// Encrypting
		aesEncrypt(expandedKey, inP, encP);

		// Decrypting
		aesDecrypt(expandedKey, encP, decP);
		
		inP = input + i * SIZE_16;
		encP = encOutput + i * SIZE_16;
		decP = decOutput + i * SIZE_16;
	}
}	

