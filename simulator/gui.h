#ifndef GUI_HEADER
#define GUI_HEADER

#include <SDL2/SDL.h>
#include <stdio.h>
#include "../api.h"
#include "../laby/laby.h"
#include "../utils.h"

/// @brief Initialise the GUI by creating the window and the renderer
/// @param matrix The previously generated matrix to show in background
/// @return A pointer to the created window
SDL_Window* init_gui(matrix_t matrix);

/// @brief Function to call to refresh the GUI
/// @param rob The robot structure representing it
/// @param known_matrix The actual know matrix by the robot
/// @param size The size of the known matrix
void refresh_gui(robot_t *rob, matrix_t known_matrix, int size);

/// @brief Function to call at the end to free the SDL library
void destroy_gui();

/// @brief Draw the representation of a matrix on the renderer
/// @param renderer The renderer where to draw
/// @param matrix The matrix to draw
/// @param size The size of the matrix
void draw_matrix(SDL_Renderer *renderer, matrix_t matrix, int size);

#endif