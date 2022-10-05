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

void refresh_gui(int pos_x, int pos_y, uint8_t **known_matrix, int size)
{
    // main refresh
    //set black as background clear
    SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
    SDL_RenderClear(main_renderer);

    SDL_SetRenderDrawColor(main_renderer, 252, 3, 23, 100);
    draw_matrix(main_renderer, global_matrix, LABY_CELL_NUMBER);

    SDL_RenderPresent(main_renderer);
}

int check_bit(uint8_t byteFlag, int whichBit)
{
    if (whichBit > 0 && whichBit <= 8)
        return (byteFlag & (1<<(whichBit-1)));
    else
        return 0;
}

void draw_matrix(SDL_Renderer *renderer, uint8_t **matrix, int size)
{
    int win_height = SDL_GetWindowSurface(main_window)->h;
    int win_width = SDL_GetWindowSurface(main_window)->w;
    int height_is_max = win_height > win_width;
    int win_size = height_is_max ? win_width : win_height;
    draw_scale = (float)win_size/(LABY_CELL_NUMBER*LABY_CELL_SIZE);
    int offset_x = 0;
    int offset_y = 0;
    if (height_is_max) {
      offset_y = (win_height - win_size)/2;
    } else {
      offset_x = (win_width - win_size)/2;
    }

    SDL_Rect verti_wall = {0, 0, WALL_WIDTH*draw_scale, LABY_CELL_SIZE*draw_scale};
    SDL_Rect horiz_wall = {0, 0, LABY_CELL_SIZE*draw_scale, WALL_WIDTH*draw_scale};
    int i = 0;
    int j = 0;

    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            //up wall
            if(check_bit(matrix[i][j], 1)) {
                horiz_wall.x = draw_scale*(j*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_x;
                horiz_wall.y = draw_scale*(i*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_y;
                SDL_RenderFillRect(renderer, &horiz_wall);
            }
            //left wall
            if(check_bit(matrix[i][j], 4)) {
                verti_wall.x = draw_scale*(j*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_x;
                verti_wall.y = draw_scale*(i*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_y;
                SDL_RenderFillRect(renderer, &verti_wall);
            }
            //right wall if we are at the last col
            if(j == size-1 && check_bit(matrix[i][j], 2)) {
                verti_wall.x = draw_scale*((j+1)*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_x;
                verti_wall.y = draw_scale*(i*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_y;
                SDL_RenderFillRect(renderer, &verti_wall);
            }
            // bottom wall if we are at the last raw
            if(i == size-1 && check_bit(matrix[i][j], 3)) {
                horiz_wall.x = draw_scale*(j*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_x;
                horiz_wall.y = draw_scale*((i+1)*LABY_CELL_SIZE - WALL_WIDTH/2) + offset_y;
                SDL_RenderFillRect(renderer, &horiz_wall);
            }
        }
    }
}

void destroy_gui()
{
    SDL_DestroyRenderer(main_renderer);
    SDL_Quit();
}
