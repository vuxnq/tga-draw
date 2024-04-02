#pragma once
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI acos(-1)
#define MAX_LENGTH 256

typedef unsigned char byte;

typedef struct {
  int x, y;
} POSITION;

typedef struct {
  int r, g, b, a;
} COLOUR;

char* strreverse(char* str);
bool is_digit(char* string);
bool check_params(char* params, int count);
bool check_colour(COLOUR* colour);
