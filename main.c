#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "laby/laby.h"
#include "simulator/gui.h"
#include "utils.h"
#include "api.h"

int main(int argc, char** argv)
{
    SDL_Event event;
    uint8_t **matrix, **unknow;
    struct timespec start, end;
    long delta_time;
    // init a robot
    robot rob = {{90., 90., 0}, 0};

    //matrix generation
    matrix = create_2D_array(LABY_CELL_NUMBER, 255);
    gen_laby_from(LABY_CELL_NUMBER, matrix);
    unknow = create_2D_array(LABY_CELL_NUMBER, 0);

    /* init functions from modules */
    init_gui(matrix);
    middleware_init();

    // test move to position
    position t = { LABY_CELL_SIZE * 9.5, LABY_CELL_SIZE * 9.5, 0};
    middleware_goto_position(&rob, &t, 500);

    while(1) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        /* Event loop */
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                goto noerror;
                break;

            default:
                break;
        }

        //update gui and robot position
        simulator_update_position(&rob, (float)DELTA_TIME/1000);
        refresh_gui(&rob, unknow, LABY_CELL_NUMBER);

        //wait the time remaining to get to DELTA_TIME
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        delta_time = (long)(DELTA_TIME*1000) - (end.tv_nsec - start.tv_nsec)/1000;
        if(delta_time >= 0)
            usleep(delta_time);
        else {
            fprintf(stdout, "Error delta time is short, or functions call are too long !\n");
            exit(EXIT_FAILURE);
        }
    }

    fprintf(stdout, "Erreur lors de la récupération d'évenement (%s)", SDL_GetError());

noerror:
    /* free everything */
    free_2D_array(matrix, LABY_CELL_NUMBER);
    destroy_gui();

    return EXIT_SUCCESS;
}
