#include <stdio.h>
#include <stdlib.h>
#include "laby_conf.h"
#include "gui/gui.h"

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

int main(int argc, char** argv)
{
    SDL_Event event;
    uint8_t **matrix;

    matrix = create_2D_array(LABY_CELL_NUMBER, 255);

    init_gui(matrix);

    while(1) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                goto noerror;
                break;

            default:
                break;
        }

        refresh_gui(0, 0, 0, 0);

        SDL_Delay(10);
    }

    fprintf(stdout, "Erreur lors de la récupération d'évenement (%s)", SDL_GetError());

noerror:
    free_2D_array(matrix, LABY_CELL_NUMBER);
    destroy_gui();

    return EXIT_SUCCESS;
}
