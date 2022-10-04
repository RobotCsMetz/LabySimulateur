#ifndef GUI_HEADER
#define GUI_HEADER

#include <SDL2/SDL.h>
#include <stdio.h>
#include "../api.h"

/// @brief Initialise l'interface SDL et crée une fenêtre dont la taille est spécifié en argument
/// @return le pointeur vers la fenêtre créée
SDL_Window* init_gui(int win_size, uint8_t **matrix);

void destroy_gui();

void draw_matrix(SDL_Window *pWindow, uint8_t **matrix, int size);

#endif