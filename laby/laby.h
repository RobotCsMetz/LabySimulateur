#ifndef LABY_HEADER
#define LABY_HEADER

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "../api.h"
#include "laby_conf.h"

/// @brief Generate a maze randomly
/// @param size The size of the maze (the matrix)
/// @param matrix the matrix where the maze is written
void gen_laby_from(int size, matrix_t matrix);

/// @brief Import a laby with the saved format (look at laby_export_format.txt) and create his matrix
/// @param laby_path The path to the laby txt file
/// @return the pointer to the matrix
matrix_t import_laby_from(char *laby_path);

/// @brief Wrtie the matrix to ./saved/laby_{timestamp}.txt with the save format
/// @param matrix The matrix to save
void output_laby_from(matrix_t matrix);

#endif
