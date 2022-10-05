/*
 * This file aims to simulate the reality by impleting functions declared in api.h
 * All the physic stands here !
 */

#include <memory.h>
#include "../api.h"

robot *saved_robot;

uint8_t middleware_init()
{

    return 1;
}

uint8_t middleware_get_robot_position(robot *new_robot)
{
    new_robot = saved_robot;
    return 1;
}

/* Simulator functions */

void simulator_update_position(robot *rob, float delta_time)
{
    //just had the velocity vector times the delta time to the pos
    if(saved_robot == NULL)
        saved_robot = rob;

    if(rob == NULL)
        return;

    rob->posi.pos_x += (float)saved_robot->speed * delta_time * cosf(rob->posi.angle*2*M_PI/360);
    rob->posi.pos_y += (float)saved_robot->speed * delta_time * sinf(rob->posi.angle*2*M_PI/360);
    saved_robot = rob;
}