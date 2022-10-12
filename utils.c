#include "utils.h"

matrix_t create_2D_array(int size, uint8_t val)
{
    matrix_t ptr;
    int i=0;
    ptr = malloc(sizeof(matrix_t)*size);
    for(i=0; i < size; i++) {
        ptr[i] = malloc(sizeof(uint8_t)*size);
        memset(ptr[i], val, sizeof(uint8_t)*size);
    }

    return ptr;
}

void free_2D_array(matrix_t array, int size)
{
    int i;
    for(i=0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}

matrix_t copy_2D_array(matrix_t src, int size)
{
    int i,j;
    matrix_t ptr = create_2D_array(size, 0);
    for(i=0; i < size; i++) {
        for(j=0; j < size; j++) {
            ptr[i][j] = src[i][j];
        }
    }

    return ptr;
}