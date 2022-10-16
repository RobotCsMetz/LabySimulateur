#ifndef SIMULATOR_HEADER
#define SIMULATOR_HEADER

#define DELTA_TIME 20 //delta time between update in ms
#define MAX_ACCEL 20000 //(in mm/s²), calculate with a PFD ma = F
#define RADIUS_POINT_PRECISION 4 // radius of the cirlce detection in mm

#define TELEMETER_MAX_DISTANCE 300

/* aliases for useful functions */
#define sensors_read_values(read_dest, rob) simulator_simulate_read_sensors(read_dest, rob)


void simulator_init(matrix_t real_matrix, robot_t *real_robot);

/// @brief Update the position of the robot at each loop call
/// @param rob The saved robot_t object
/// @param delta_time Delta time between two call (in s)
void simulator_update_position(robot_t *rob, float delta_time);

/// @brief Overlapping function for middleware_goto_position
/// @param rob the robot struct
/// @param target_pos the destination position
/// @param speed the speed
void simulator_goto_position(robot_t *rob, position_t target_pos, float speed);

/// @brief Simulate the read of the sensors (we can add some randomness)
/// @param read_dest The struct where to write the sensors values
void simulator_simulate_read_sensors(sensor_values_t *read_dest, robot_t *rob);

uint8_t simulator_position_reached(robot_t *rob);

#endif
