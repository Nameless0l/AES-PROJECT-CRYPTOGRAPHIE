#include "data.h"

int main(int argc, char **argv) {
	srand(time(NULL));
	
	int inputLength, nBlock;
	Byte *input, *encOutput, *decOutput;
	Byte key[SIZE_16] = "TEAMSCORPIAN1234";
	Byte expandedKey[(NROUNDS + 1) * SIZE_16];

	// Welcome
	printf("*** AES ENCRYPTION AND DECRYPTION ***\n\n");
	
	// Read message to encrypt
	input = readEntry("Enter your message : ", &inputLength, &nBlock);
	printf("\n");
	
	// Generation of the NROUNDS keys
	keyExpansion(key, expandedKey);
		
	// Displaying Key data
	printBytes("KEY", key, SIZE_16);
	
	// Encrypting and Decrypting message
	const int finalSize = nBlock * SIZE_16 * sizeof(Byte);
	encOutput = (Byte*)malloc(finalSize);
	decOutput = (Byte*)malloc(finalSize);
	
	// AES's Main function
	aesMain(expandedKey, input, nBlock, encOutput, decOutput);
	
	// Displaying Encrypted and Decrypted texts
	printBytes("ENCRYPTED OUTPUT AND NEW INPUT FOR DECRYPTION", encOutput, inputLength);
	printBytes("DECRYPTED OUTPUT", transpose(decOutput, nBlock), inputLength);
	
	return EXIT_SUCCESS;
}
