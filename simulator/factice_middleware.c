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

void simulator_update_position(robot *rob, float delta_time)
{
    //just had the velocity vector times the delta time to the pos
    if(rob == NULL)
        return;

    rob->posi.pos_x += rob->speed * delta_time * cos(rob->posi.angle);
    rob->posi.pos_y += rob->speed * delta_time * sin(rob->posi.angle);
}