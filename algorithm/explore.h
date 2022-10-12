#ifndef EXPLORE_HEADER
#define EXPLORE_HEADER

#include "../api.h"

/* State machine for exploring */
#define EXPLORE_STATE_MOVE 1
#define EXPLORE_STATE_WAIT_POS_REACHED 5
#define EXPLORE_STATE_UPDATE_MATRIX 6

/// @brief Init the explore state machine
/// @param default_state The default state
void explore_init_state(const uint8_t default_state);

/// @brief The explore main state machine loop
/// @param rob The robot struct
void explore_state_machine(robot_t *rob);

#endif