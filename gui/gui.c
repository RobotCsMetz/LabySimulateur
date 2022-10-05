#include "gui.h"

/* static vars */
uint8_t **global_matrix;
SDL_Window *main_window;
SDL_Renderer *main_renderer;
SDL_Texture *robot_img;
int ori_robot_w, ori_robot_h;
float draw_scale;
int win_size, offset_x, offset_y;

void auto_scale()
{
    SDL_Surface *m_s = SDL_GetWindowSurface(main_window);
    if(!m_s) {
        fprintf(stdout, "Error can't get window surface for rescaling (%s).\n", SDL_GetError());
        return;
    }
    /* calculate window size and draw scale */
    int win_height = m_s->h;
    int win_width = m_s->w;
    int height_is_max = win_height > win_width;
    int win_size = height_is_max ? win_width : win_height;
    draw_scale = (float)win_size/(LABY_CELL_NUMBER*LABY_CELL_SIZE);

    /* calculate offset */
    offset_x = offset_y = 0;
    if (height_is_max) {
        offset_y = (win_height - win_size)/2;
    } else {
        offset_x = (win_width - win_size)/2;
    }
}

SDL_Window* init_gui(uint8_t **matrix)
{

    SDL_DisplayMode DM;
    global_matrix = matrix;

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return NULL;
    }

    /* get height of screen for scaling */
    SDL_GetDesktopDisplayMode(0, &DM);
    win_size = DM.h;

    /* Création de la fenêtre */
    main_window = SDL_CreateWindow("Simulateur de labyrinthe",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                win_size,
                                win_size,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if( main_window == NULL ) {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return NULL;
    }

    main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

    if(!main_renderer) {
        fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
        return NULL;
    }

    //SDL_Rect viewport = {0, 0, win_size, win_size};
    //SDL_RenderSetViewport(main_renderer, &viewport);
    SDL_SetRenderDrawBlendMode(main_renderer, SDL_BLENDMODE_BLEND); // for alpha channel

    /* Load robot image */
    SDL_Surface *s = SDL_LoadBMP("../robot.bmp");
    robot_img = SDL_CreateTextureFromSurface(main_renderer, s);
    SDL_SetTextureBlendMode(robot_img, SDL_BLENDMODE_NONE);
    ori_robot_h = s->h;
    ori_robot_w = s->w;
    SDL_FreeSurface(s);

    auto_scale();

    return main_window;
}

void refresh_gui(int pos_x, int pos_y, double angle, uint8_t **known_matrix, int size)
{
    // main refresh
    auto_scale();
    //set black as background clear
    SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
    SDL_RenderClear(main_renderer);

    //base lab
    SDL_SetRenderDrawColor(main_renderer, 252, 3, 23, 100);
    draw_matrix(main_renderer, global_matrix, LABY_CELL_NUMBER);

    //known_lab
    if(known_matrix) {
        SDL_SetRenderDrawColor(main_renderer, 10, 255, 10, 210);
        draw_matrix(main_renderer, known_matrix, LABY_CELL_NUMBER);
    }

    //draw robot
    int height = (draw_scale*LABY_CELL_SIZE)/2;
    int width = ori_robot_w*height/ori_robot_h;
    SDL_Rect r = {pos_x*draw_scale + offset_x, pos_y*draw_scale + offset_y, width, height};
    SDL_RenderCopyEx(main_renderer, robot_img, NULL, &r, 180 + angle, NULL, SDL_FLIP_NONE);

    SDL_RenderPresent(main_renderer);
}

void draw_matrix(SDL_Renderer *renderer, uint8_t **matrix, int size)
{
    // prefiled rect for wall
    SDL_Rect verti_wall = {0, 0, WALL_WIDTH*draw_scale, LABY_CELL_SIZE*draw_scale};
    SDL_Rect horiz_wall = {0, 0, LABY_CELL_SIZE*draw_scale, WALL_WIDTH*draw_scale};
    int i = 0;
    int j = 0;

    for(i=0; i < size; i++) {
        for(j = 0; j < size; j++) {
            //up wall
            if(check_bit(matrix[i][j], 1)) {
                horiz_wall.x = (i*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_x;
                horiz_wall.y = (j*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_y;
                SDL_RenderFillRect(renderer, &horiz_wall);
            }
            //right wall
            if(check_bit(matrix[i][j], 2)) {
                verti_wall.x = ((i+1)*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_x;
                verti_wall.y = (j*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_y;
                SDL_RenderFillRect(renderer, &verti_wall);
            }
            //bottom wall
            if(check_bit(matrix[i][j], 3)) {
                horiz_wall.x = (i*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_x;
                horiz_wall.y = ((j+1)*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_y;
                SDL_RenderFillRect(renderer, &horiz_wall);
            }
            //left wall
            if(check_bit(matrix[i][j], 4)) {
                verti_wall.x = (i*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_x;
                verti_wall.y = (j*LABY_CELL_SIZE*draw_scale - WALL_WIDTH*draw_scale/2) + offset_y;
                SDL_RenderFillRect(renderer, &verti_wall);
            }
        }
    }
}

void destroy_gui()
{
    SDL_DestroyTexture(robot_img);
    SDL_DestroyRenderer(main_renderer);
    SDL_Quit();
}
