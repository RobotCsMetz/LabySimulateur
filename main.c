#include <stdio.h>
#include <stdlib.h>
#include "laby_conf.h"
#include "gui/gui.h"

int main(int argc, char** argv)
{
    SDL_Event event;
    uint8_t matrix[LABY_CELL_NUMBER][LABY_CELL_NUMBER];
    memset((void *)matrix, 0xffff, LABY_CELL_NUMBER*LABY_CELL_NUMBER/2);

    init_gui((uint8_t **)matrix);

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
    destroy_gui();

    return EXIT_SUCCESS;
}
