#ifndef LABY_HEADER
#define LABY_HEADER

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "laby_conf.h"

/// @brief Generate a maze randomly
/// @param size The size of the maze (the matrix)
/// @param matrix the matrix where the maze is written
void gen_laby_from(int size, uint8_t **matrix);

#endif