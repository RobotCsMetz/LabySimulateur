#ifndef SIMULATOR_HEADER
#define SIMULATOR_HEADER

#define DELTA_TIME 20 //delta time between update in ms
#define MAX_ACCEL 100 //(in mm/s²), calculate with a PFD ma = F

/// @brief Update the position of the robot at each loop call
/// @param rob The saved robot object
/// @param delta_time Delta time between two call (in s)
void simulator_update_position(robot *rob, float delta_time);

void simulator_update_velocity(robot *rob, float accel, float delta_time);

#endif