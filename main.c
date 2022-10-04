#include <stdio.h>
#include <stdlib.h>
#include "laby_conf.h"
#include "gui/gui.h"
#include "utils.h"

int main(int argc, char** argv)
{
    SDL_Event event;
    uint8_t **matrix, **unknow;

    matrix = create_2D_array(LABY_CELL_NUMBER, 255);
    unknow = copy_2D_array(matrix, LABY_CELL_NUMBER);
    unknow[3][3] = 0;
    unknow[4][3] = 0;

    init_gui(matrix);

    while(1) {
        /* Event loop */
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                goto noerror;
                break;

            default:
                break;
        }

        refresh_gui(0, 0, 0, unknow, LABY_CELL_NUMBER);

        SDL_Delay(10);
    }

    fprintf(stdout, "Erreur lors de la récupération d'évenement (%s)", SDL_GetError());

noerror:
    /* free everything */
    free_2D_array(matrix, LABY_CELL_NUMBER);
    destroy_gui();

    return EXIT_SUCCESS;
}
