#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/// @brief Allocate memory and initialise value with val of a 2D square shape array
/// @param size Dimension of the array, the result is a size*size matrice
/// @param val Default value of each case
/// @return pointer to a list of pointer of uint8_t to the allocated memory
uint8_t **create_2D_array(int size, uint8_t val);

/// @brief Free the allocated memory of a 2D array
/// @param array the array as a pointer to a list of pointer
/// @param size dimension of the array
void free_2D_array(uint8_t **array, int size);

/// @brief Copy a 2D array to another
/// @param src Source array
/// @param size Size of the source array
/// @return The newly copied array with a new memory space
uint8_t **copy_2D_array(uint8_t **src, int size);

/// @brief Check a bit in a byte value
/// @param byteFlag The byte to check
/// @param whichBit The bit number to check (1-8)
/// @return the bit value (0 or 1)
int check_bit(uint8_t byteFlag, int whichBit);

#endif