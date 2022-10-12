#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "../utils.h"
#include "laby.h"

void gen_laby_from(int size, matrix_t matrix)
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
    while (pow(end[1] - start[1], 2) + pow(end[0] - start[0], 2) < pow(LABY_CELL_NUMBER, 2)/2 + 4 || 0 == end[0] || end[0] == LABY_CELL_NUMBER || 0 == end[1] || end[1] == LABY_CELL_NUMBER) {
        end[0] = rand() % (LABY_CELL_NUMBER-1);
        end[1] = rand() % (LABY_CELL_NUMBER-1);
    }
    // A path from the origin to the flag is randomly generated
    int case_x[LABY_CELL_NUMBER*2];
    int case_y[LABY_CELL_NUMBER*2];
    int path_found = 0;
    int i = 0;
    int i_jump = 0;
    int ite = 0;
    int is_there_any_hole = 1;
    while (is_there_any_hole) {
        printf("Flag : %d|%d\n", end[0], end[1]);
        is_there_any_hole = 0;
        while (!path_found) {
            ite++;
            if (ite > 50) {
                ite = 0;
                end[0] = LABY_CELL_NUMBER-2;
                end[1] = 0;
                while (pow(end[1] - start[1], 2) + pow(end[0] - start[0], 2) < pow(LABY_CELL_NUMBER, 2)/2 + 4 || 0 == end[0] || end[0] == LABY_CELL_NUMBER || 0 == end[1] || end[1] == LABY_CELL_NUMBER) {
                    end[0] = rand() % (LABY_CELL_NUMBER-1);
                    end[1] = rand() % (LABY_CELL_NUMBER-1);
                }
            }
            // printf("%s\n", "new atp");
            // printf("Flag : %d|%d\n", end[0], end[1]);
            int current_pos[] = {LABY_CELL_NUMBER-2,0};
            i = 0;
            i_jump = 0;
            // printf("Cur : %d|%d\n", current_pos[0], current_pos[1]);
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
                // printf("Cur : %d|%d\n", current_pos[0], current_pos[1]);
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
                if (i == end[0]) {
                    if (j == end[1]) {
                        if (case_x[path_length] - case_x[path_length-1] == 1) {
                            // Destroy right and bottom wall
                            r = (r | 6) ^ 6;
                            // Add left wall
                            r = r | 8;
                            matrix[i][j-1] = matrix[i][j-1] | 2;
                        } else {
                            // Destroy right wall
                            r = (r | 2) ^ 2;
                            // Add bottom OR left wall
                            if (abs(case_x[path_length]-case_x[path_length-1]) == 1) {
                                r = r | 8;
                                matrix[i][j-1] = matrix[i][j-1] | 2;
                            } else {
                                r = r | 4;
                            }
                        }
                    } else if (j == end[1] + 1) {
                        if (case_x[path_length] - case_x[path_length-1] == 1) {
                            // Destroy left and bottom wall
                            r = (r | 12) ^ 12;
                            // Add top and right wall
                            r = r | 3;
                            matrix[i-1][j] = matrix[i-1][j] | 4;
                        } else {
                            // Add bottom and right wall
                            r = r | 6;
                        }
                    }
                } else {
                    if (case_x[path_length] - case_x[path_length-1] == 1) {
                        if (i == end[0] + 1) {
                            if (j == end[1]) {
                                // Destroy right and top wall
                                r = (r | 3) ^ 3;
                                // Add bottom and left wall
                                r = r | 12;
                                matrix[i][j-1] = matrix[i][j-1] | 2;
                            } else if (j == end[1] + 1) {
                                // Destroy top and bottom wall
                                r = (r | 5) ^ 5;
                                matrix[i-1][j] = matrix[i-1][j] | 4;
                                // Add bottom and right wall
                                r = r | 6;
                            }
                        }
                    } else {
                        if (i == end[0] - 1) {
                            if (j == end[1]) {
                                // Destroy right and bottom wall
                                r = (r | 6) ^ 6;
                                // Add top and left wall
                                r = r | 9;
                                matrix[i-1][j] = matrix[i-1][j] | 4;
                                matrix[i][j-1] = matrix[i][j-1] | 2;
                            } else if (j == end[1] + 1) {
                                // Destroy bottom wall
                                r = (r | 4) ^ 4;
                                // Add top and right wall
                                r = r | 3;
                                matrix[i-1][j] = matrix[i-1][j] | 4;
                            }
                        }
                    }
                }
                // Avoid plain square
                if (r == 15) {
                    int q = pow(rand() % 2 + 1, 2);
                    r = r ^ q;
                }
                matrix[i][j] = r;
            }
        }
        // Find closed area and open them
        // int spread_area = 0;
        // int ite = 0;
        // int i = 0;
        // int j = 0;
        // int visited_x[(int)pow(LABY_CELL_NUMBER, 2)];
        // int visited_y[(int)pow(LABY_CELL_NUMBER, 2)];
        // int stack_x[(int)pow(LABY_CELL_NUMBER, 2)];
        // int stack_y[(int)pow(LABY_CELL_NUMBER, 2)];
        // while (spread_area != pow(LABY_CELL_NUMBER, 2)) {
        //     visited_x[i] = i;
        //     if (!check_bit(matrix[i][j], 1)) {
        //         stack_x[i] = i-1;
        //         stack_y[i] = j;
        //     }
        //     if (!check_bit(matrix[i][j], 2)) {
        //         stack_x[i] = i;
        //         stack_y[i] = j+1;
        //     }
        //     if (!check_bit(matrix[i][j], 3)) {
        //         stack_x[i] = i+1;
        //         stack_y[i] = j;
        //     }
        //     if (!check_bit(matrix[i][j], 4)) {
        //         stack_x[i] = i;
        //         stack_y[i] = j-1;
        //     }
        //     i++;
        //     j++;
        // }
        // If some missing node are missing retry the wall process
        int p = 0;
        int arrival_detected = 0;
        for (int i = 1; i < size; i++) {
            for (int j = 1; j < size; j++) {
                if (!check_bit(matrix[i-1][j-1], 2) && !check_bit(matrix[i-1][j-1], 3)
                && !check_bit(matrix[i][j], 1) && !check_bit(matrix[i][j], 4)) {
                    p++;
                    if ((end[0] == i || end[0] == i - 1) && (end[1] == j || end[1] == j - 1)) {
                        if (!arrival_detected) {
                            // Arrival detected (expected)
                            arrival_detected = 1;
                            continue;
                        } else {
                            is_there_any_hole = 1;
                            printf("Some hole were found, retry \n");
                        }
                    } else {
                        is_there_any_hole = 1;
                        printf("Some hole were found, retry \n");
                    }
                }
            }
        }
    }
}
