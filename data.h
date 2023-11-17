#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define SIZE_16 16
#define NROUNDS 10
#define BUF_SIZE 255

#define IN // Not used, Just for formality
#define OUT // For variables intented to store final values of functions
#define HYB // For variables intented to play the IN and OUT roles

typedef uint8_t Byte;

#include "common.h"
#include "encrypt.h"
#include "decrypt.h"

#endif //__DATA_H__
