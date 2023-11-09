#include "functions.h"

int main(int argc, char **argv) {
    Byte input[SIZE_16], output[SIZE_16];
    Byte key[SIZE_16] = "TEAMSCORPIAN1234";
    
	createInput("MESSAGEENCRPTION", input);
	aesEncrypt(key, input, output);
    
    printBytes("KEY", key);
    printBytes("INPUT", input);
    printBytes("OUTPUT", output);

    return 0;
}
