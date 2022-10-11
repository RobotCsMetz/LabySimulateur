/*
 * This file aims to simulate the reality by impleting functions declared in api.h
 * All the physic stands here !
 */

#include <memory.h>
#include <stdlib.h>
#include "../api.h"

uint8_t middleware_init()
{
    return 1;
}

uint8_t middleware_get_robot_position(robot_t *new_robot)
{
    return 1;
}

void middleware_goto_position(robot_t *rob, position_t target_pos, float speed)
{
    simulator_goto_position(rob, target_pos, speed);
}

uint8_t middleware_wall_position(robot_t *rob)
{
    //vars
    sensor_values_t vals;
    uint8_t ret_byte;

    //get sensors values
    sensors_read_values(&vals);

    //compute values with current position to know if there is a wall

}
