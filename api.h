#ifndef API_HEADER
#define API_HEADER

#include <stdint.h>
#include <math.h>

//time in ms between to absolute position calculation
#define POSITION_UPDATE_RATE 1000/50
#define LIDAR_VIEW_ANGLE (float)M_PI/2 // in radian
#define LIDAR_RESOLV 8 // The length of the buf return by the lidar

#define DEFAULT_EXPLORE_MOVE_SPEED 1000 // 2 m/s default travel speed

/* define for movement */

#define MOVE_UP 1
#define MOVE_RIGHT 2
#define MOVE_LEFT 3
#define MOVE_DOWN 4

/* end define          */

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

/// @brief Initialise every sensors, variables and the initial robot for the middleware
/// @return 1 if succeed, 0 otherwise
uint8_t middleware_init(robot_t *rob, matrix_t mat);

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

/// @brief Overlapping function to make the robot move number_of_cell in direction. Useful for exploration
/// @param rob The robot struct
/// @param number_of_cell Number of cell to move
/// @param direction Direction given by the flags MOVE_*
void middleware_move_cell(robot_t *rob, uint8_t number_of_cell, uint8_t direction);

/// @brief Detect the wall around the robot and return the corresponding matrix value
/// @param rob The current robot structure
/// @return The matrix value (bits : 1 -> up, 2 -> left, 3 -> bottom, 4 -> left)
uint8_t middleware_wall_position(robot_t *rob);

/// @brief Tell if the position previously given was reached or not
/// @param rob The robot structure
/// @return 1 if the position was reached, 0 otherwise
uint8_t middleware_position_reached(robot_t *rob);

/// @brief Stop the robot as fast as possible
void middleware_stop();

#ifdef SIMULATOR
#include "simulator/simulator.h"
#endif

#endif
