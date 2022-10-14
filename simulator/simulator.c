/* files containing simulator functions */

#include <memory.h>
#include <stdlib.h>
#include "../api.h"
#include <stdio.h>
#include <math.h>
#include "../laby/laby_conf.h"
#include "../utils.h"

robot_t *saved_robot = NULL;
position_t dest_pos = {-1, -1};
float travel_speed, accel_time;
float current_timer;
matrix_t matrix;

void simulator_init(matrix_t real_matrix, robot_t *real_robot)
{
    matrix = real_matrix;
    saved_robot = real_robot;
}

void simulator_goto_position(robot_t *rob, position_t target_pos, float speed)
{
    dest_pos = target_pos;
    travel_speed = speed;
    accel_time = speed/MAX_ACCEL;
    rob->posi.angle = atanf((dest_pos.pos_y - rob->posi.pos_y)/(dest_pos.pos_x - rob->posi.pos_x));
    current_timer = 0;
}

void simulator_simulate_read_sensors(sensor_values_t *read_dest, robot_t *rob)
{
    // The idea here is to simulate what the lidar see
    // To mimic a real situation, some noise will be introduced
    // This noise is induce by ITE_STEP, the higher it is, the lower the resolution, a value of x mean ±x (mm) of precision.
    const float ITE_STEP = 1;
    float lidar_val[LIDAR_RESOLV];
    float angle = rob->posi.angle;
    while (angle <= 0) angle += 2*M_PI;
    for (int i = 0; i < LIDAR_RESOLV; i++) {
        float x = rob->posi.pos_x;
        float y = rob->posi.pos_y;
        int reverse_xy = 0;
        float tmp_angle = angle + (i-(float)(LIDAR_RESOLV-1)/2)*(float)LIDAR_VIEW_ANGLE/LIDAR_RESOLV;
        while (tmp_angle > 2*M_PI) tmp_angle -= 2*M_PI;
        while (tmp_angle <= 0) tmp_angle += 2*M_PI;
        if ((tmp_angle > M_PI/4 && tmp_angle < 3*M_PI/4) || (tmp_angle > 5*M_PI/4 && tmp_angle < 7*M_PI/4)) {
            reverse_xy = 1;
            if (tmp_angle < M_PI/2) tmp_angle = M_PI/2 - tmp_angle;
            else if (tmp_angle < M_PI) tmp_angle = 3*M_PI/2 - tmp_angle ;
            else if (tmp_angle < 3*M_PI/2) tmp_angle = 5*M_PI/2 - tmp_angle ;
            else tmp_angle = 7*M_PI/2 - tmp_angle;
        }
        // The slope value is now always reasonable
        float slope = tanf(tmp_angle);
        int intercept = 0;
        while (!intercept) {
            float x_mod = x;
            float y_mod = y;
            int ix = 0;
            int iy = 0;
            while (x_mod > LABY_CELL_SIZE) {
                x_mod -= LABY_CELL_SIZE;
                ix++;
            }
            while (y_mod > LABY_CELL_SIZE) {
                y_mod -= LABY_CELL_SIZE;
                iy++;
            }
            if (ix >= LABY_CELL_NUMBER) ix = LABY_CELL_NUMBER-1;
            if (iy >= LABY_CELL_NUMBER) iy = LABY_CELL_NUMBER-1;
            if (x_mod < 2*ITE_STEP) {
                // Potentially hit the left wall, check its presence
                if (check_bit(matrix[iy][ix], 8)) {
                    intercept = 1;
                }
            } else if (x_mod > LABY_CELL_SIZE - 2*ITE_STEP) {
                // Potentially hit the right wall, check its presence
                if (check_bit(matrix[iy][ix], 2)) {
                    intercept = 1;
                }
            }
            if (y_mod < 2*ITE_STEP) {
                // Potentially hit the top wall, check its presence
                if (check_bit(matrix[iy][ix], 1)) {
                    intercept = 1;
                }
            } else if (y_mod > LABY_CELL_SIZE - 2*ITE_STEP) {
                // Potentially hit the bottom wall, check its presence
                if (check_bit(matrix[iy][ix], 4)) {
                    intercept = 1;
                }
            }
            if (intercept) {
                lidar_val[i] = sqrt(pow(x - rob->posi.pos_x, 2) + pow(y - rob->posi.pos_y, 2));
            } else {
                if (!reverse_xy) {
                    if (tmp_angle < M_PI/2 || tmp_angle > 3*M_PI/2) {
                        x += ITE_STEP;
                        y -= slope*ITE_STEP;
                    } else {
                        x -= ITE_STEP;
                        y += slope*ITE_STEP;
                    }
                } else {
                    if (tmp_angle < M_PI) {
                        y -= ITE_STEP;
                        x += slope*ITE_STEP;
                    } else {
                        y += ITE_STEP;
                        x -= slope*ITE_STEP;
                    }
                } 
            }
        }
    }
    // for (int i = 0; i < LIDAR_RESOLV; i++) {
    //     printf("|%f|", lidar_val[i]);
    // }
    // printf("\n");
}

void simulator_update_position(robot_t *rob, float delta_time)
{
    //just had the velocity vector times the delta time to the pos
    if(saved_robot == NULL)
        saved_robot = rob;

    if(rob == NULL || dest_pos.pos_x != -1)
        return;

    rob->posi.pos_x += (float)rob->speed * delta_time * cosf(rob->posi.angle);
    rob->posi.pos_y += (float)rob->speed * delta_time * sinf(rob->posi.angle);
    saved_robot = rob;

    // Update rob velocity
    if(pow((rob->posi.pos_x - dest_pos.pos_x), 2) + pow((rob->posi.pos_y - dest_pos.pos_y), 2) > pow(RADIUS_POINT_PRECISION, 2)) {
        // Accel phase
        if(current_timer < accel_time) {
            rob->speed = MAX_ACCEL * current_timer;
        } else {
            rob->speed = travel_speed;
        }
    } else {
        rob->speed = 0;
    }

    current_timer += delta_time;
}
