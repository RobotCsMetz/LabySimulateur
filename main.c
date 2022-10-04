#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

void **gen_laby_from(int size, uint8_t **matrix)
{
    // 0 -> empty
    // 1 -> haut
    // 2 -> droite
    // 3 -> haut droite
    // 4 -> haut bas
    // 5 -> bas
    // 6 -> droite bas
    // 7 -> haut droite bas
    // 8 -> haut gauche
    // 9 -> gauche
    // 10 -> droite gauche
    // 11 -> bas gauche
    // 12 -> haut droite gauche
    // 13 -> haut bas gauche
    // 14 -> droite bas gauche
    // 15 -> haut droite bas gauche

    srand(time(NULL));
    // The beginning is set at the case : (9,0)
    int start[] = {LABY_CELL_NUMBER-2,0};
    // The end is randomly generated far enough
    int end[] = {LABY_CELL_NUMBER-2,0};
    while (pow(end[1] - start[1], 2) + pow(end[0] - start[0], 2) < pow(LABY_CELL_NUMBER, 2)/2 + 4) {
        end[0] = rand() % (LABY_CELL_NUMBER-1);
        end[1] = rand() % (LABY_CELL_NUMBER-1);
    }
    printf("Flag : %d|%d\n", end[0], end[1]);
    // A path from the origin to the flag is randomly generated
    int case_x[LABY_CELL_NUMBER*2];
    int case_y[LABY_CELL_NUMBER*2];
    int path_found = 0;
    int i = 0;
    int i_jump = 0;
    int ite = 0;
    while (!path_found) {
        ite++;
        if (ite > 50) {
            ite = 0;
            end[0] = LABY_CELL_NUMBER-2;
            end[1] = 0;
            while (pow(end[1] - start[1], 2) + pow(end[0] - start[0], 2) < pow(LABY_CELL_NUMBER, 2)/2 + 4) {
                end[0] = rand() % (LABY_CELL_NUMBER-1);
                end[1] = rand() % (LABY_CELL_NUMBER-1);
            }
        }
        printf("%s\n", "new atp");
        printf("Flag : %d|%d\n", end[0], end[1]);
        int current_pos[] = {LABY_CELL_NUMBER-2,0};
        i = 0;
        i_jump = 0;
        printf("Cur : %d|%d\n", current_pos[0], current_pos[1]);
        while ((current_pos[0] != end[0] || current_pos[1] != end[1]) && i < LABY_CELL_NUMBER*2) {
            case_x[i-i_jump] = current_pos[0];
            case_y[i-i_jump] = current_pos[1];
            i++;
            int found = 0;
            while (!found) {
                found = 1;
                // Attractor
                if (i % 3 == 0) {
                    if (i % 6 == 0) {
                        end[0] - current_pos[0] == 0 ? 0 : (end[0] - current_pos[0] > 0 ? current_pos[0]++ : current_pos[0]--);
                    } else {
                        end[1] - current_pos[1] == 0 ? 0 : (end[1] - current_pos[1] > 0 ? current_pos[1]++ : current_pos[1]--);
                    }
                    // Can force to go back on its step, thus increase i to skip it next time
                    i++;
                    i_jump++;
                } else {
                    int randint = rand() % 3 - 1;
                    if (i % 2 == 0) {
                        current_pos[0] = current_pos[0] + randint;
                    } else {
                        current_pos[1] = current_pos[1] + randint;
                    }
                }
                // Check overflow
                current_pos[0] = current_pos[0] < 0 ? 0 : current_pos[0];
                current_pos[1] = current_pos[1] < 0 ? 0 : current_pos[1];
                current_pos[0] = current_pos[0] > (LABY_CELL_NUMBER-1) ? LABY_CELL_NUMBER-1 : current_pos[0];
                current_pos[1] = current_pos[1] > (LABY_CELL_NUMBER-1) ? LABY_CELL_NUMBER-1 : current_pos[1];
                for (int j = 0; j < i; j++) {
                    if (current_pos[0] == case_x[j] && current_pos[1] == case_y[j]) {
                        found = 0;
                    }
                }
            }
            printf("Cur : %d|%d\n", current_pos[0], current_pos[1]);
        }
        if (i < LABY_CELL_NUMBER*2) {
            path_found = 1;
            case_x[i-i_jump] = current_pos[0];
            case_y[i-i_jump] = current_pos[1];
            // In some peculiar cases a diagonal jump can be observe, thus the continuity of the pathy must be checked
            for (int k = 1; k <= i-i_jump; k++) {
                if (case_x[k] != case_x[k-1] && case_y[k] != case_y[k-1]) {
                    path_found = 0;
                    break;
                }
            }
        }
    }
    int path_length = i-i_jump;
    printf("%s\n", "Path found !");
    // Generating wall without intercepting previous path
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int r = rand() % 16;
            // TODO ...
            matrix[i][j] = r;
        }
    }
}

int main(int argc, char** argv)
{
    SDL_Event event;
    uint8_t **matrix;

    matrix = create_2D_array(LABY_CELL_NUMBER, 255);
    gen_laby_from(LABY_CELL_NUMBER, matrix);

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
