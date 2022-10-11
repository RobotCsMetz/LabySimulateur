#ifndef SIMULATOR_HEADER
#define SIMULATOR_HEADER

#define DELTA_TIME 20 //delta time between update in ms
#define MAX_ACCEL 250 //(in mm/s²), calculate with a PFD ma = F
#define RADIUS_POINT_PRECISION 4 // 1mm precision

/// @brief Update the position of the robot at each loop call
/// @param rob The saved robot_t object
/// @param delta_time Delta time between two call (in s)
void simulator_update_position(robot_t *rob, float delta_time);

void simulator_update_velocity(robot_t *rob, float accel, float delta_time);

#endif