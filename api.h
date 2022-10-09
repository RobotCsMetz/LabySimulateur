#ifndef API_HEADER
#define API_HEADER

#include <stdint.h>
#include <math.h>

//time in ms between to position calculation
#define POSITION_UPDATE_RATE 1000/50

/* ### Structures declaration ### */

/// @brief Structure of a positon in mm and deg
typedef struct position {
    float pos_x;
    float pos_y;
    //angle du robot en degré, origine à droite (cercle trigo)
    double angle;
} position;

/// @brief Structure representing the robot state at time t
typedef struct robot {
    position posi;

    //speed in the angle direction (in mm/s)
    float speed;
} robot;
/* ### end structures ### */

/* ### real functions declarations ### */

/// @brief Initialise every sensors and var for the middleware
/// @return 1 if succeed, 0 otherwise
uint8_t middleware_init();

/// @brief Read sensors and compute values to give the robot current position (normally called every 20ms, 50Hz)
/// @param new_robot The next robot state where values will be stored
/// @return 1 if function succeed, 0 otherwise
uint8_t middleware_get_robot_position(robot *new_robot);

/// @brief Move the robot straightforward to the point pos
/// @param rob The current robot
/// @param target_pos The target position
/// @param travel_speed The max speed reached during travel (mm/s)
/// @return
void middleware_goto_position(robot *rob, position *target_pos, float travel_speed);

/// @brief Stop the robot as fast as possible
void middleware_stop();

#ifdef SIMULATOR
#include "simulator/simulator.h"
#endif

#endif