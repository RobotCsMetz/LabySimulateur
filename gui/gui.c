#include "gui.h"

uint8_t **global_matrix;
SDL_Window *main_window;
SDL_Renderer *main_renderer;

SDL_Window* init_gui(uint8_t **matrix)
{
    int win_size;
    SDL_Window* pWindow = NULL;
    SDL_DisplayMode DM;

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return NULL;
    }

    /* calculate window size */
    SDL_GetCurrentDisplayMode(0, &DM);
    win_size = DM.h;

    /* Création de la fenêtre */
    pWindow = SDL_CreateWindow("Simulateur de labyrinthe",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                win_size,
                                win_size,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if( pWindow == NULL ) {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return NULL;
    }

    main_renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    if(!main_renderer) {
        fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
        return NULL;
    }

    global_matrix = matrix;
    main_window = pWindow;

    return pWindow;
}

void refresh_gui(int pos_x, int pos_y, uint8_t **known_matrix, int size)
{
    // main loop

    //set black as background clear
    SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
    SDL_RenderClear(main_renderer);




    SDL_RenderPresent(main_renderer);
}

void draw_matrix(SDL_Window *pWindow, uint8_t **matrix, int size)
{

}

void destroy_gui() 
{
    SDL_DestroyRenderer(main_renderer);
    SDL_Quit();
}