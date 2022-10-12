#include "state.h"
#include "explore.h"

static uint8_t current_state, next_state;

void init_state(const uint8_t default_state)
{
    current_state = next_state = default_state;

    explore_init_state(EXPLORE_STATE_UPDATE_MATRIX);
}

void state_loop(robot_t *rob)
{
    switch (current_state)
    {
        case STATE_STANDBY:
            next_state = STATE_SEARCH;
            break;

        case STATE_SEARCH:
            explore_state_machine(rob);
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