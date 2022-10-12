#ifndef API_HEADER
#define API_HEADER

#include <stdint.h>
#include <math.h>

//time in ms between to absolute position calculation
#define POSITION_UPDATE_RATE 1000/50

/* special type */
typedef uint8_t** matrix_t;
/* end special type */

/* ### Structures declaration ### */

/// @brief Structure of a positon in mm and deg
typedef struct position_t {
    float pos_x;
    float pos_y;
    //angle du robot_t en radian, origine à droite (cercle trigo)
    float angle;
} position_t;

/// @brief Structure representing the robot_t state at time t
typedef struct robot_t {
    position_t posi;

    //speed in the angle direction (in mm/s)
    float speed;
} robot_t;

/// @brief struct for the values of sensors
typedef struct sensor_values {
    //infrared telemeter distance in mm
    float front_telemeter;
    float left_telemeter;
    float right_telement;

} sensor_values_t;
/* ### end structures ### */

/* ### real functions declarations ### */

/// @brief Initialise every sensors and var for the middleware
/// @return 1 if succeed, 0 otherwise
uint8_t middleware_init();

/// @brief Read sensors and compute values to give the robot_t current position (normally called every 20ms, 50Hz)
/// @param new_robot_t The next robot_t state where values will be stored
/// @return 1 if function succeed, 0 otherwise
uint8_t middleware_get_robot_position(robot_t *new_robot);

/// @brief Move the robot_t straightforward to the point pos
/// @param rob The current robot_t
/// @param target_pos The target position
/// @param travel_speed The max speed reached during travel (mm/s)
/// @return
void middleware_goto_position(robot_t *rob, position_t target_pos, float travel_speed);

/// @brief Detect the wall around the robot and return the corresponding matrix value
/// @param rob The current robot structure
/// @return The matrix value (bits : 1 -> up, 2 -> left, 3 -> bottom, 4 -> left)
uint8_t middleware_wall_position(robot_t *rob);

/// @brief Stop the robot as fast as possible
void middleware_stop();

#ifdef SIMULATOR
#include "simulator/simulator.h"
#endif

#endif