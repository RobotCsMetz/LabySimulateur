#include "explore.h"

static uint8_t current_state, next_state;
uint8_t cell_count = 1, move_direction = 0;
uint8_t wall_flag;

void explore_init_state(const uint8_t default_state)
{
    current_state = next_state = default_state;
}

void explore_state_machine(robot_t *rob)
{
    switch (current_state)
    {
        case EXPLORE_STATE_MOVE:
            middleware_move_cell(rob, cell_count, move_direction);
            next_state = EXPLORE_STATE_WAIT_POS_REACHED;
            break;

        case EXPLORE_STATE_WAIT_POS_REACHED:
            if(middleware_position_reached(rob)) {
                next_state = EXPLORE_STATE_UPDATE_MATRIX;
            }
            break;

        case EXPLORE_STATE_UPDATE_MATRIX:
            wall_flag = middleware_wall_position(rob);

            move_direction = MOVE_RIGHT;
            next_state = EXPLORE_STATE_MOVE;
            break;
    }

    current_state = next_state;
}