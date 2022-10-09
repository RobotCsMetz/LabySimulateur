/*
 * This file aims to simulate the reality by impleting functions declared in api.h
 * All the physic stands here !
 */

#include <memory.h>
#include <stdlib.h>
#include "../api.h"

robot *saved_robot;
position *dest_pos;
float travel_speed, accel_time;
float current_timer;

uint8_t middleware_init()
{

    return 1;
}

uint8_t middleware_get_robot_position(robot *new_robot)
{
    new_robot = saved_robot;
    return 1;
}

void middleware_goto_position(robot *rob, position *target_pos, float speed)
{
    dest_pos = target_pos;
    travel_speed = speed;
    accel_time = speed/MAX_ACCEL;
    rob->posi.angle = atanf((dest_pos->pos_y - rob->posi.pos_y)/(dest_pos->pos_x - rob->posi.pos_x))*180/M_PI;
    current_timer = 0;
}

/* Simulator functions */

void simulator_update_position(robot *rob, float delta_time)
{
    //just had the velocity vector times the delta time to the pos
    if(saved_robot == NULL)
        saved_robot = rob;

    if(rob == NULL)
        return;

    rob->posi.pos_x += (float)rob->speed * delta_time * cosf(rob->posi.angle*2*M_PI/360);
    rob->posi.pos_y += (float)rob->speed * delta_time * sinf(rob->posi.angle*2*M_PI/360);
    saved_robot = rob;

    //update rob velocity
    if(pow((rob->posi.pos_x - dest_pos->pos_x), 2) + pow((rob->posi.pos_y - dest_pos->pos_y), 2) > pow(RADIUS_POINT_PRECISION, 2)) {
        //accel phase
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