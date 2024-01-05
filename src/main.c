#include "../include/data.h"

int main(int argc, char **argv) {
    /* All the variables for the program :
        * encryptedOutput : Input message encrypted
        * decryptedOutput : Input message decrypted
        * expandedKey : Contains all the NROUNDS + 1 keys
        * input : Entry of the user
        * key : Key for encryption - decryption
     */
	Byte encryptedOutput[SIZE_16], decryptedOutput[SIZE_16];
	Byte expandedKey[(NROUNDS + 1) * SIZE_16];
    Byte input[SIZE_16] = "MESSAGEENCRPTION";
    Byte key[SIZE_16] = "TEAMSCORPIAN1234";
    
    // Welcome
    printf("*** AES ENCRYPTION AND DECRYPTION ***\n\n");
    
    // Generation of the NROUNDS keys
    keyExpansion(key, expandedKey);
    
    // Encrypting
	aesEncrypt(expandedKey, input, encryptedOutput);
	
    // Decrypting
    aesDecrypt(expandedKey, encryptedOutput, decryptedOutput);
    
    // Displaying Key and Input data, Encrypted and Decrypted texts
    printBytes("KEY", key);
    printBytes("INPUT", input);
	printBytes("ENCRYPTED OUTPUT AND NEW INPUT FOR DECRYPTION", encryptedOutput);
	printBytes("DECRYPTED OUTPUT", decryptedOutput);
    
    return EXIT_SUCCESS;
}
