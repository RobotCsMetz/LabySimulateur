#ifndef STATE_CONF_HEADER
#define STATE_CONF_HEADER

#include <stdint.h>
#include "../api.h"

#define STATE_STANDBY 1
#define STATE_SEARCH 2
#define STATE_PATH_FINDING 3
#define STATE_RUN 4

/// @brief Init function for the the main state machine
/// @param default_state First state of the state machine
void init_state(const uint8_t default_state);

/// @brief Main state loop for the algorithm
/// @param rob Struct representing the robot when calling the loop
void state_loop(robot_t *rob);

#endif