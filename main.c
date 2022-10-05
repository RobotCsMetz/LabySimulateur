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
    // 4 -> bas
    // 5 -> haut bas
    // 6 -> droite bas
    // 7 -> haut droite bas
    // 8 -> gauche
    // 9 -> haut gauche
    // 10 -> droite gauche
    // 11 -> haut droite gauche
    // 12 -> bas gauche
    // 13 -> haut bas gauche
    // 14 -> droite bas gauche
    // 15 -> haut droite bas gauche

    srand(time(NULL));
    // The beginning is set at the case : (9,0)
    int start[] = {LABY_CELL_NUMBER-2,0};
    // The end is randomly generated far enough
    int end[] = {LABY_CELL_NUMBER-2,0};
    while (pow(end[1] - start[1], 2) + pow(end[0] - start[0], 2) < pow(LABY_CELL_NUMBER, 2)/2 + 4 && end[0] > 0 && end[1] < LABY_CELL_NUMBER) {
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
            while (pow(end[1] - start[1], 2) + pow(end[0] - start[0], 2) < pow(LABY_CELL_NUMBER, 2)/2 + 4 && end[0] > 0 && end[1] < LABY_CELL_NUMBER) {
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
            // In some peculiar cases a diagonal jump can be observe, thus the continuity of the path must be checked
            for (int k = 1; k <= i-i_jump; k++) {
                if (case_x[k] != case_x[k-1] && case_y[k] != case_y[k-1]) {
                    path_found = 0;
                    break;
                }
                if (abs(case_x[k]-case_x[k-1]) != 1 && abs(case_y[k]-case_y[k-1]) != 1) {
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
            int r = rand() % 3;
            switch (r) {
                case 0:
                    r = 2;
                    break;
                case 1:
                    r = 4;
                    break;
                case 2:
                    r = 4;
                    break;
            }
            if (i != 0 && check_bit(matrix[i-1][j], 3)) {
                // Add top wall
                r = r | 1;
            }
            if (j != 0 && check_bit(matrix[i][j-1], 2)) {
                // Add left wall
                r = r | 8;
            }
            if (i == 0) {
                // Add top wall
                r = r | 1;
            }
            if (i == size-1) {
                // Add bottom wall
                r = r | 4;
            }
            if (j == 0) {
                // Add left wall
                r = r | 8;
            }
            if (j == size-1) {
                // Add right wall
                r = r | 2;
            }
            for (int k = 0; k <= path_length; k++) {
                if (case_x[k] == i && case_y[k] == j) {
                    if ((case_x[k+1] == i+1 || (k != 0 && case_x[k-1] == i+1))&& check_bit(r, 3)) {
                        // Destroy bottom wall
                        r = r ^ 4;
                    }
                    if ((case_y[k+1] == j+1 || (k != 0 && case_y[k-1] == j+1)) && check_bit(r, 2)) {
                        // Destroy right wall
                        r = r ^ 2;
                    }
                    break;
                }
            }
            // The 2x2 arrival area is created in the top right corner of the end
            // Some space exist 'cause of the last conditions in the while in charge of determining end
            // TODO : compute it from the las two elemements of case_x/y
            if (i == end[0]) {
                if (j == end[1]) {
                    // Destroy right wall
                    r = (r | 2) ^ 2;
                    // Add bottom OR left wall
                    if (abs(case_x[path_length]-case_x[path_length-1]) == 1) {
                        r = r | 8;
                    } else {
                        r = r | 4;
                    }
                } else if (j == end[1] + 1) {
                    // Add bottom and right wall
                    r = r | 6;
                }
            } else if (i == end[0] - 1) {
                if (j == end[1]) {
                    // Destroy right and bottom wall
                    r = (r | 2) ^ 2;
                    r = (r | 4) ^ 4;
                    // Add top and left wall
                    r = r | 9;
                    matrix[i-1][j] = matrix[i-1][j] | 4;
                    if (j != 0) matrix[i][j-1] = matrix[i][j-1] | 2;
                } else if (j == end[1] + 1) {
                    // Destroy bottom wall
                    r = (r | 4) ^ 4;
                    // Add top and right wall
                    r = r | 3;
                    matrix[i-1][j] = matrix[i-1][j] | 4;
                    matrix[i][j-1] = matrix[i][j-1] | 8;
                }
            }
            // Avoid plain square
            if (r == 15) {
                int q = pow(rand() % 2 + 1, 2);
                r = r ^ q;
            }
            matrix[i][j] = r;
            // TODO fix closed area (spreading algo for each case while the spread != LABY_CELL_NUMBER² then find a wall to remove)
            // TODO fix missing node caused by removing wall for the path
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
