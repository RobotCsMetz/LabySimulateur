/* files containing simulator functions */

#include <memory.h>
#include <stdlib.h>
#include "../api.h"

robot_t *saved_robot = NULL;
position_t dest_pos = {-1, -1, 0};
float travel_speed, accel_time;
float current_timer;
matrix_t matrix;

void simulator_init(matrix_t real_matrix, robot_t *real_robot)
{
    matrix = real_matrix;
    //saved_robot = real_robot;
}

void simulator_goto_position(robot_t *rob, position_t target_pos, float speed)
{
    dest_pos = target_pos;
    travel_speed = speed;
    accel_time = speed/MAX_ACCEL;
    rob->posi.angle = atanf((dest_pos.pos_y - rob->posi.pos_y)/(dest_pos.pos_x - rob->posi.pos_x));
    //if angle is over pi/2 or -pi/2, mirror the abscisse value
    if(dest_pos.pos_x - rob->posi.pos_x < 0) {
        rob->posi.angle = M_PI - rob->posi.angle;
    }

    current_timer = 0;
}

void simulator_simulate_read_sensors(sensor_values_t *read_dest)
{
    /* TODO : recreate the real sensors value */
}

void simulator_update_position(robot_t *rob, float delta_time)
{
    // just had the velocity vector times the delta time to the pos
    if(rob == NULL || dest_pos.pos_x == -1) {
        return;
    }

    rob->posi.pos_x += (float)rob->speed * delta_time * cosf(rob->posi.angle);
    rob->posi.pos_y += (float)rob->speed * delta_time * sinf(rob->posi.angle);
    //saved_robot = rob;

    //update rob velocity
    if(pow((rob->posi.pos_x - dest_pos.pos_x), 2) + pow((rob->posi.pos_y - dest_pos.pos_y), 2) > pow(RADIUS_POINT_PRECISION, 2)) {
        //accel phase
        if(current_timer < accel_time) {
            rob->speed = MAX_ACCEL * current_timer;
        } else {
            rob->speed = travel_speed;
        }
    } else {
        rob->speed = 0;
        dest_pos.pos_x = -1;
        dest_pos.pos_y = -1;
    }

    current_timer += delta_time;
}

uint8_t simulator_position_reached(robot_t *rob)
{
    return dest_pos.pos_x == -1;
}