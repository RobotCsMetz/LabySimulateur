#include "utils.h"

uint8_t **create_2D_array(int size, uint8_t val)
{
    uint8_t **ptr;
    int i=0;
    ptr = malloc(sizeof(uint8_t*)*size);
    for(i=0; i < size; i++) {
        ptr[i] = malloc(sizeof(uint8_t)*size);
        memset(ptr[i], val, sizeof(uint8_t)*size);
    }

    return ptr;
}

void free_2D_array(uint8_t **array, int size)
{
    int i;
    for(i=0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}

uint8_t **copy_2D_array(uint8_t **src, int size)
{
    int i,j;
    uint8_t **ptr = create_2D_array(size, 0);
    for(i=0; i < size; i++) {
        for(j=0; j < size; j++) {
            ptr[i][j] = src[i][j];
        }
    }

    return ptr;
}

int check_bit(uint8_t byteFlag, int whichBit)
{
    if (whichBit > 0 && whichBit <= 8)
        return (byteFlag & (1<<(whichBit-1)));
    else
        return 0;
}
