#include "state.h"
#include "explore.h"

uint8_t current_state, next_state;

void init_state(const uint8_t default_state)
{
    current_state = next_state = default_state;
}

void state_loop(robot_t *rob)
{
    switch (current_state)
    {
        case STATE_STANDBY:
            next_state = STATE_SEARCH;
            break;

        case STATE_SEARCH:
            explore(rob);
            break;

        case STATE_PATH_FINDING:
            break;

        case STATE_RUN:
            break;

        default:
            break;
    }

    current_state = next_state;
}