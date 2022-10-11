#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "laby.h"
#include "../utils.h"

uint8_t** import_laby_from(char *laby_path)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    uint8_t **matrix, **unknow;
    matrix = create_2D_array(LABY_CELL_NUMBER, 0);

    fp = fopen(laby_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int line_cnt = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[0] != '#') {
            int i = 0;
            int column_cnt = 0;
            int space_cnt = 0;
            while (i < read) {
                if (space_cnt == 4) {
                    space_cnt = 0;
                    column_cnt++;
                    // Return no wall
                }
                if (line[i] != ' ') {
                    space_cnt = 0;
                    if (i < read-2 && line[i+1] != ' ') {
                        // Return bottom and right wall
                        matrix[line_cnt][column_cnt] = 6;
                    } else {
                        if (line[i] == 's') {
                            // Return bottom wall
                            matrix[line_cnt][column_cnt] = 4;

                        } else if (line[i] == 'd') {
                            // Return right wall
                            matrix[line_cnt][column_cnt] = 2;
                        }
                    }
                    i++;
                    column_cnt++;
                } else {
                    space_cnt++;
                }
                // Needed to avoid peculiar cases where a letter is encounter twice with 2 differents posiions (1 and then 2, creating 4 blank spaces)
                i++;
            }
            line_cnt++;
        }
    }
    for (int i = 0; i < LABY_CELL_NUMBER; i++) {
        for (int j = 0; j < LABY_CELL_NUMBER;j++) {
            int r = matrix[i][j];
            if (i != 0 && check_bit(matrix[i-1][j], 3)) {
                // Add top wall
                r = r ^ 1 | 1;
            }
            if (j != 0 && check_bit(matrix[i][j-1], 2)) {
                // Add left wall
                r = r ^ 8 | 8;
            }
            if (i == 0) {
                // Add top wall
                r = r ^ 1 | 1;
            }
            if (i == LABY_CELL_NUMBER-1) {
                // Add bottom wall
                r = r ^ 4 | 4;
            }
            if (j == 0) {
                // Add left wall
                r = r ^ 8 | 8;
            }
            if (j == LABY_CELL_NUMBER-1) {
                // Add right wall
                r = r ^ 2 | 2;
            }
            matrix[i][j] = r;
        }
    }

    fclose(fp);
    return matrix;
}

void output_laby_from(uint8_t **matrix)
{
    int cnt = 0;
    char stringify[4*LABY_CELL_NUMBER*LABY_CELL_NUMBER+LABY_CELL_NUMBER];
    for (int i = 0; i < LABY_CELL_NUMBER; i++) {
        for (int j = 0; j < LABY_CELL_NUMBER; j++) {
            if (i != LABY_CELL_NUMBER-1 && check_bit(matrix[i][j], 3)) {
                // Add bottom wall
                stringify[cnt] = 's';
            } else {
                stringify[cnt] = ' ';
            }
            cnt++;
            if (j != LABY_CELL_NUMBER-1 && check_bit(matrix[i][j], 2)) {
                // Add right wall
                stringify[cnt] = 'd';
            } else {
                stringify[cnt] = ' ';
            }
            cnt++;
            stringify[cnt] = ' ';
            stringify[cnt+1] = ' ';
            cnt += 2;
        }
        stringify[cnt] = '\n';
        cnt++;
    }

    time_t now = time(0);
    char path[29];
    snprintf(path, 29, "../saved/laby_%ld.txt", now); // puts string into buffer
    FILE *fptr;
    fptr = fopen(path,"w");
    if(fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    fprintf(fptr,"%s",stringify);
    fclose(fptr);

    printf("laby saved to '%s'\n", path);
}
