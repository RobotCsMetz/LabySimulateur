#include <memory.h>
#include <stdlib.h>
#include "../laby/laby_conf.h"
#include "../api.h"
#include <stdio.h>

matrix_t real_laby;

uint8_t middleware_init(robot_t *rob, matrix_t mat)
{
    real_laby = mat;
    //robot init
    //the robot start at cell (1, MAX_NUMBER - 1 )
    rob->posi.pos_x = LABY_CELL_SIZE/2; //middle of x cell
    rob->posi.pos_y = (LABY_CELL_NUMBER - 1.5)*LABY_CELL_SIZE;

    rob->posi.angle = 0;

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

void middleware_move_cell(robot_t *rob, uint8_t number_of_cell, uint8_t direction)
{
    position_t dest = rob->posi;

    switch (direction)
    {
        case MOVE_UP:
            dest.pos_y += LABY_CELL_SIZE*number_of_cell;
            break;

        case MOVE_RIGHT:
            dest.pos_x += LABY_CELL_SIZE*number_of_cell;
            break;

        case MOVE_DOWN:
            dest.pos_y -= LABY_CELL_SIZE*number_of_cell;
            break;

        case MOVE_LEFT:
            dest.pos_x -= LABY_CELL_SIZE*number_of_cell;
            break;
    }

    middleware_goto_position(rob, dest, DEFAULT_EXPLORE_MOVE_SPEED);
}

uint8_t middleware_wall_position(robot_t *rob)
{
    //vars
    sensor_values_t vals;
    uint8_t ret_byte;

    //get sensors values
    sensors_read_values(&vals, rob);

    //compute values with current position to know if there is a wall

}

uint8_t middleware_position_reached(robot_t *rob)
{
    return simulator_position_reached(rob);
}
