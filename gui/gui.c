#include "gui.h"

uint8_t **global_matrix;
SDL_Window *main_window;

SDL_Window* init_gui(int win_size, uint8_t **matrix)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return NULL;
    }

    /* Création de la fenêtre */
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Simulateur de labyrinthe",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                win_size,
                                win_size,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);

    if( pWindow == NULL ) {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return NULL;
    }

    global_matrix = matrix;
    main_window = pWindow;

    return pWindow;
}

void draw_matrix(SDL_Window *pWindow, uint8_t **matrix, int size)
{

}

void destroy_gui() { SDL_Quit(); }