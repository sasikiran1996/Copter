#ifndef ARENA_H_INCLUDED
#define ARENA_H_INCLUDED 

/*contains all the functions related to arena generation and detecting collision with arena are here*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "variables.h"
#include "constants.h"
#include "my_texture.h"
#include "heli.h"

/*constructs the arena every frame*/
void construct_arena(SDL_Rect* clip_1,SDL_Rect* clip_2,int* x_1,int* x_2,int* ys_1,int* ys_2,int* xs_1,int* xs_2);

/*detects collision b/w heli and arena*/
bool detect_collision(SDL_Rect* wall_1,SDL_Rect* wall_2);

#endif /*ARENA_H_INCLUDED*/
