#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "encrypt.h"
#include "decrypt.h"

#define SIZE_16 16
#define NROUNDS 10
#define BUF_SIZE 255

typedef uint8_t Byte;