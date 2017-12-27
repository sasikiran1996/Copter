#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

/*File to be included in all the files stating all the variables used as extern*/
/*extern states to ignore the absence of declaration in respective files*/
/*extern says that they are declared elsewhere*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "my_texture.h"
#include "my_timer.h"
#include "heli.h"


extern SDL_Window* main_window;
extern SDL_Renderer* main_renderer;
extern my_texture* heli_texture;
extern my_texture* background_texture;
extern my_texture* sprite_sheet_1;
extern my_texture* sprite_sheet_2;
extern SDL_Rect* sprite_clip;
extern heli* main_heli;
extern SDL_Rect* background_collision_sprite;
extern SDL_Rect* heli_parts;
extern my_timer* score_timer;
extern Mix_Music* heli_running;
extern Mix_Chunk* heli_crashed;


#endif /*VARIABLES_H_INCLUDED*/
