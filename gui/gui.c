#include "gui.h"

uint8_t **global_matrix;
SDL_Window *main_window;
SDL_Renderer *main_renderer;
float draw_scale;

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
    SDL_GetDesktopDisplayMode(0, &DM);
    win_size = DM.h - 50;
    draw_scale = (float)win_size/(LABY_CELL_NUMBER*LABY_CELL_SIZE);

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

    SDL_Rect viewport = {0, 0, win_size, win_size};
    SDL_RenderSetViewport(main_renderer, &viewport);
    SDL_SetRenderDrawBlendMode(main_renderer, SDL_BLENDMODE_BLEND); // for alpha channel

    global_matrix = matrix;
    main_window = pWindow;

    return pWindow;
}

void refresh_gui(int pos_x, int pos_y, int angle, uint8_t **known_matrix, int size)
{
    // main refresh
    //set black as background clear
    SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
    SDL_RenderClear(main_renderer);

    //base lab
    SDL_SetRenderDrawColor(main_renderer, 252, 3, 23, 100);
    draw_matrix(main_renderer, global_matrix, LABY_CELL_NUMBER);

    //know_lab
    if(known_matrix) {
        SDL_SetRenderDrawColor(main_renderer, 10, 255, 10, 210);
        draw_matrix(main_renderer, known_matrix, LABY_CELL_NUMBER);
    }

    SDL_RenderPresent(main_renderer);
}

void draw_matrix(SDL_Renderer *renderer, uint8_t **matrix, int size)
{
    SDL_Rect verti_wall = {0, 0, WALL_WIDTH*draw_scale, LABY_CELL_SIZE*draw_scale};
    SDL_Rect horiz_wall = {0, 0, LABY_CELL_SIZE*draw_scale, WALL_WIDTH*draw_scale};
    int i = 0;
    int j = 0;

    for(i=0; i < size; i++) {
        for(j = 0; j < size; j++) {
            //up wall
            if(check_bit(matrix[i][j], 1)) {
                horiz_wall.x = j*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                horiz_wall.y = i*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                SDL_RenderFillRect(renderer, &horiz_wall);
            }
            //right wall
            if(check_bit(matrix[i][j], 2)) {
                verti_wall.x = (j+1)*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                verti_wall.y = i*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                SDL_RenderFillRect(renderer, &verti_wall);
            }
            //bottom wall
            if(check_bit(matrix[i][j], 3)) {
                horiz_wall.x = j*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                horiz_wall.y = (i+1)*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                SDL_RenderFillRect(renderer, &horiz_wall);
            }
            //left wall
            if(check_bit(matrix[i][j], 4)) {
                verti_wall.x = j*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                verti_wall.y = i*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2;
                SDL_RenderFillRect(renderer, &verti_wall);
            }
        }
    }
}

void destroy_gui()
{
    SDL_DestroyRenderer(main_renderer);
    SDL_Quit();
}