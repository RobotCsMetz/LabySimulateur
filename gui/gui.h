#ifndef GUI_HEADER
#define GUI_HEADER

#include <SDL2/SDL.h>
#include <stdio.h>
#include "../api.h"
#include "../laby_conf.h"

/// @brief Initialise l'interface SDL et crée une fenêtre dont la taille est spécifié en argument
/// @return le pointeur vers la fenêtre créée
SDL_Window* init_gui(uint8_t **matrix);

void refresh_gui(int pos_x, int pos_y, uint8_t **known_matrix, int size);

void destroy_gui();

void draw_matrix(SDL_Renderer *renderer, uint8_t **matrix, int size);

#endif