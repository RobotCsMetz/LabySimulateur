#include "explore.h"

uint8_t test = 0;

void explore(robot_t *rob)
{
    if(test == 0) {
        middleware_move_cell(rob, 1, MOVE_RIGHT);
        test = 1;
    }
}